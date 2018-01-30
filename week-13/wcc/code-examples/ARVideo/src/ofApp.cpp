#include "ofApp.h"
#include "ofxCv.h"
#include "ofBitmapFont.h"

using namespace cv;
using namespace ofxCv;

// this is where the magic happens
// anything you draw in here will be drawn on top of the marker
void ofApp::drawMarker(float size, const ofColor & color){
	//ofDrawAxis(size);
    ofPushMatrix();
    
    //to show video
    ofSetColor(255,255);
    ofTranslate(-size*0.5,0,-size*0.5);
    ofRotate(90, 1, 0, 0);
    player.draw(0,0,size,size);

    //to show a box
    // move up from the center by size*.5
    // to draw a box centered at that point
    //		ofTranslate(0,size*0.5,0);
    //		ofFill();
    //		ofSetColor(color,50);
    //		ofDrawBox(size);
    //		ofNoFill();
    //		ofSetColor(color);
    //		ofDrawBox(size);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	string boardName = "boardConfiguration.yml";

    grabber.setDeviceID(1);
    grabber.initGrabber(640,480);
    video = &grabber;

	//aruco.setThreaded(false);
	aruco.setup("intrinsics.int", video->getWidth(), video->getHeight(), boardName);
	aruco.getBoardImage(board.getPixels());
	board.update();

    showMarkers = true;
    
    player.load("capture.m4v");
    player.play();

}

//--------------------------------------------------------------
void ofApp::update(){
	video->update();
	if(video->isFrameNew()){
		aruco.detectBoards(video->getPixels());
	}
    player.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	video->draw(0,0);

	//aruco.draw();

	if(showMarkers){
		for(int i=0;i<aruco.getNumMarkers();i++){ // loops over all the markers
			aruco.begin(i);                         //  and calls the drawMarker() fuction to draw custom content
			drawMarker(0.15,ofColor::white);
			aruco.end();
		}
	}

	ofSetColor(255);
	ofDrawBitmapString("markers detected: " + ofToString(aruco.getNumMarkers()),20,20);
	ofDrawBitmapString("fps " + ofToString(ofGetFrameRate()),20,40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key=='m') showMarkers = !showMarkers;
}
