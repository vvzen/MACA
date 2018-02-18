#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	video.setDeviceID(0);
    video.setDesiredFrameRate(60);
    // video.initGrabber(320,240);
    video.initGrabber(640, 480);

	debug = false;

	// GUI
    gui.setup();
	GUI_threshold = 100.0f;
	GUI_max_distance = 4;
	GUI_max_points = 200;
	GUI_bg_alpha = 0.0f;
    
	// Set the video grabber to the ofxPS3EyeGrabber if you want
	//video.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
    //video.initGrabber(640, 480);
	//video.setup(640, 480);
}

//--------------------------------------------------------------
void ofApp::update(){
	video.update();	//Decode the new frame if needed

	// Do computing only if the new frame was obtained
	if (video.isFrameNew()) {
		// Getting a new frame
		image.setFromPixels( video.getPixelsRef() );
		image.mirror(false, true);
		// Convert to grayscale image
		grayImage = image;

		// Smoothing image
		blurred = grayImage;
		blurred.blurGaussian(5);

		// Thresholding for obtaining binary image
		mask = blurred;
		mask.threshold(GUI_threshold);

		// Getting an inverted mask of image to use in contour finder
		inverted = mask;
		inverted.invert();

        // FIND INTERESTING POINTS
		cv::Mat imageCV; // in opencv a matrix is an image
		imageCV = cv::Mat(mask.getCvImage());
		// inputimage, output points array, max num of points, quality level threshold, minimum distance
		cv::goodFeaturesToTrack(imageCV, corners, GUI_max_points, 0.01, GUI_max_distance);
        
		triangulation.reset();
		// add points to delaunay
		for (int i = 0; i < corners.size(); i++){
			triangulation.addPoint(ofPoint(corners.at(i).x, corners.at(i).y));
		}
		triangulation.triangulate();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(255, 255, 255);
	ofSetColor(255, 255, 255);

	if (debug){
		int w = image.width;
		int h = image.height;
		// Original decimated image
		if (image.bAllocated){
			image.draw(0, 0, w/2, h/2);
		}

		// blurred immage
		if (blurred.bAllocated){
			blurred.draw( w/2, 0, w/2, h/2);
		}

		if (mask.bAllocated){
			// Thresholded image
			mask.draw(w, 0, w/2, h/2);
		}
		if (inverted.bAllocated){
			// Inverted image
			inverted.draw( w/2*3, 0, w/2, h/2);
		}

		ofTranslate(ofGetWidth()/2-w/2, h/2+10);
		ofSetColor(0);
		ofNoFill();
		ofDrawRectangle(0,0,w,h);

		// draw the interesting points in RED
		ofSetColor(255,0,0);
		ofFill();
		for (int i = 0; i < corners.size(); i++) {
			ofDrawEllipse(corners.at(i).x, corners.at(i).y, 3, 3);
		}

		ofSetColor(0);
		triangulation.triangleMesh.drawWireframe();
	}
	else {
		// GUI
		ofSetColor(255, 255);
		drawImGui();

		ofPushStyle();
		ofSetColor(255, GUI_bg_alpha);
		image.draw(0, 0);
		ofPopStyle();
		
		// add a triangle in our vector from each triangle
		// createad by the ofxDelaunay triangulation
		for (int g = 0; g < triangulation.getNumTriangles(); g++){
			
			// extract the vector with 3 points
			vector <ofPoint> pts = get_triangle_points(triangulation, g);
			// use the nice overloaded functions to compute the centroid
			ofPoint centroid = (pts[0] + pts[1] + pts[2]) / pts.size();
			// find relative pixel color
			ofColor pixel_color = image.getPixels().getColor(centroid.x, centroid.y);
			ofSetColor(pixel_color);
			ofDrawTriangle(pts[0], pts[1], pts[2]);
		}
	}
}

//--------------------------------------------------------------
// custom function (by Theo) that takes a triangulation object and an index
// and returns the coordinates of the triangle we refer to
// (I modified it slightly so that it's more encapsulated)
vector <ofPoint> ofApp::get_triangle_points(ofxDelaunay & triangulation, int i){

    int pA = triangulation.triangleMesh.getIndex(i*3);
    int pB = triangulation.triangleMesh.getIndex(i*3+1);
    int pC = triangulation.triangleMesh.getIndex(i*3+2);

    ofPoint pointA = triangulation.triangleMesh.getVertex(pA);
    ofPoint pointB = triangulation.triangleMesh.getVertex(pB);
    ofPoint pointC = triangulation.triangleMesh.getVertex(pC);

    vector <ofPoint> points;
    points.push_back(pointA);
    points.push_back(pointB);
    points.push_back(pointC);
    
    return points;
}

//--------------------------------------------------------------
// nice ofx addon for gui rendering, see https://github.com/jvcleave/ofxImGui
//--------------------------------------------------------------
void ofApp::drawImGui(){

	gui.begin();
	
	auto main_settings = ofxImGui::Settings();
	main_settings.windowPos = ofVec2f(10, 500);
	main_settings.windowSize = ofVec2f(0.0f, 0.0f); // auto resize

	ofxImGui::BeginWindow("GUI", main_settings, false);
	ImGui::SliderFloat("Threshold", &GUI_threshold, 0.0f, 200.0f);
	ImGui::SliderInt("Max Points", &GUI_max_points, 10, 700);
	ImGui::SliderFloat("Max Distance", &GUI_max_distance, 0.5f, 100.0f);
	ImGui::SliderFloat("Bg Alpha", &GUI_bg_alpha, 0.0f, 255.0f);
	ofxImGui::EndWindow(main_settings);
	
	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key){
		case 'd': {
			debug = !debug;
			break;
		}
	}
}