#include "ofApp.h"
#include "ofxPS3EyeGrabber.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    video.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
    // video.setDeviceID(0);
    // video.setDesiredFrameRate(120);
    video.initGrabber(640, 480);

    // video.load("dummyVideo.m4v");
    // video.play();

    debug = false;
}

//--------------------------------------------------------------
void ofApp::update(){

	video.update();	//Decode the new frame if needed

	// Do computing only if the new frame was obtained
	if (video.isFrameNew()) {
		// Getting a new frame
		image.setFromPixels(video.getPixels());

		// Convert to grayscale image
		grayImage = image;

		// Smoothing image
		blurred = grayImage;
		blurred.blurGaussian(120);

		// Store first frame to background image
		if (!background.bAllocated) {
			background = blurred;
		}

		// Find difference of the frame and background
		diff = blurred;
		diff.absDiff(blurred, background); // get pixel difference
        
		// Thresholding for obtaining binary image
		mask = diff;
		mask.threshold(ofMap(mouseX, 0, ofGetWidth(), 0, 200)); // threshold controlled by mouseX
        mask.erode_3x3();
        mask.dilate_3x3();
		// mask.threshold(53.4375);
        // It should be adjusted for good results when using another videos than in example.
		
        // Find contours
		contourFinder.findContours( mask, 10, 20000, 20, false );

		// Store objects centers
        blobs = contourFinder.blobs;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

    video.draw(0, 0);

    ofSetColor(255, 255, 255);	// Set color for images drawing

    // DEBUG MODE: draws the color image (top left), the difference from background (top right)
    // the thresholded image (bottom left) and the original image with centroids (bottom right).
    if (debug){
        int w = image.width;
        int h = image.height;
        //Original decimated image
        image.draw(0, 0, w/2, h/2);

        //Difference
        diff.draw( w/2, 0, w/2, h/2 );

        // Thresholded
        mask.draw( 0, h/2, w/2, h/2 );

        // Draw found contours
        contourFinder.draw( 0, h/2, w/2, h/2 );

        //Draw centers over decimated image
        image.draw(w/2, h/2, w/2, h/2);
        ofSetColor( 255, 255, 0 );
        ofSetLineWidth( 2 );
        ofTranslate(w/2, h/2);
        for (int i=0; i<blobs.size(); i++) {
            ofPoint p = blobs[i].centroid / ofPoint(2,2) ;
            ofDrawLine( p.x - 20, p.y, p.x + 20, p.y );
            ofDrawLine( p.x, p.y - 20, p.x, p.y + 20 );
        }
        ofSetLineWidth(1);
    }
    else {
        // Draw centers over original image and the centroids
        image.draw(0, 0);
        ofPushStyle();
        ofSetColor(255, 255, 0);
        ofSetLineWidth(2);
        for (int i = 0; i < blobs.size(); i++) {
            ofPoint p = ofPoint(blobs[i].centroid.x, blobs[i].centroid.y);
            // ofDrawCircle(p.x, p.y, 20, 20);
            // snake.addVertex(p);
            // ofDrawLine( p.x - 20, p.y, p.x + 20, p.y );
            // ofDrawLine( p.x, p.y - 20, p.x, p.y + 20 );
        }

        snake.draw();

        ofPopStyle();
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    debug = !debug;
    cout << "mouse x: " << x << " y: " << y << endl;
    snake.clear();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int button){
   background = blurred;
}
