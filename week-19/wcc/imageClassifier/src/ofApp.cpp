#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    hand_detector.setup("data.json");
    cam.initGrabber(640, 480, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    cout << "Class is: " << hand_detector.run(cam.getPixels()) << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.draw(0, 0);
}
