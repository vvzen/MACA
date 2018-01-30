#include "ofApp.h"
#include "ofxCv.h"
#include "ofBitmapFont.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	string boardName = "boardConfiguration.yml";

    grabber.setDeviceID(0);
    grabber.initGrabber(640,480);
    video = &grabber;

	//aruco.setThreaded(false);
	aruco.setup("intrinsics.int", video->getWidth(), video->getHeight(), boardName);
	aruco.getBoardImage(board.getPixels());
	board.update();

	showMarkers = true;
}

//--------------------------------------------------------------
void ofApp::update(){
	video->update();
	if(video->isFrameNew()){
		aruco.detectBoards(video->getPixels());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
    video->draw(0,0);//,ofGetWidth(), ofGetHeight());

	//aruco.draw();

    //getting 2D position + rotation around Z axis
	if(showMarkers){
		for(int i=0;i<aruco.getNumMarkers();i++){ // loop over all the markers

            ofPushMatrix();
            ofPushStyle();
            
            ofVec2f pos;
            pos.x = aruco.getMarkers()[0].getCenter().x;  // get the x coord
            pos.y = aruco.getMarkers()[0].getCenter().y;  // get the y coord
            cv::Mat rotationVector = aruco.getMarkers()[0].Rvec; // get the rotation vector
            float rotationZ = rotationVector.at<float>(0,2); // extract the rotation Z
            rotationZ = ofMap(rotationZ, -2.35, 2.35, 0, 360, true); // map it to angles

            // draw something with the location + rotation
            ofNoFill();
            ofTranslate(pos);
            ofRotateZ(rotationZ);
            ofSetColor(255,0,0);
            ofSetLineWidth(3);
            ofDrawEllipse(0,0, 30,30);
            ofDrawLine(0,0,15,0);
            
            ofPopStyle();
            ofPopMatrix();
		}
	}

	ofDrawBitmapString("markers detected: " + ofToString(aruco.getNumMarkers()),20,20);
	ofDrawBitmapString("fps " + ofToString(ofGetFrameRate()),20,40);
	ofDrawBitmapString("m toggles markers",20,60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key=='m') showMarkers = !showMarkers;
}
