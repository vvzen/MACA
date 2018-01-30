#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	finder.setup("haarcascade_frontalface_default.xml");

    videoGrabber.setDeviceID(0);
    videoGrabber.setDesiredFrameRate(30);
    videoGrabber.initGrabber(320, 240);
}

//--------------------------------------------------------------
void ofApp::update(){
    finder.setScaleHaar(1.1);
    videoGrabber.update();
    img.setFromPixels(videoGrabber.getPixels());
	finder.findHaarObjects(img);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofNoFill();
    img.draw(0, 0);

    if(videoGrabber.isFrameNew()){
        for(unsigned int i = 0; i < finder.blobs.size(); i++) { // loop over all the found faces/blobs
            ofRectangle cur = finder.blobs[i].boundingRect;     // and put a rectangle around the face
            ofDrawRectangle(cur);
        }
    }

}
