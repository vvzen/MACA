#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    theta = ofMap(mouseX,0,ofGetWidth(),0,90);
    // Start the tree from the bottom of the screen
    ofTranslate(ofGetWidth()/2, ofGetHeight());
    branch(200);
}
//--------------------------------------------------------------
void ofApp::branch(float len) {
    // Each branch will be 2/3rds the size of the previous one
    ofSetColor(255);
    ofSetLineWidth(2);

    ofDrawLine(0, 0, 0, -len);
    // Move to the end of that line
    ofTranslate(0, -len);

    len *= 0.7f;
    // All recursive functions must have an exit condition!!!!
    // Here, ours is when the length of the branch is 2 pixels or less
    if (len > 2) {
      ofPushMatrix();    // Save the current state of transformation (i.e. where are we now)
      ofRotate(theta);   // Rotate by theta
      branch(len);       // Ok, now call myself to draw two new branches!!
      ofPopMatrix();     // Whenever we get back here, we "pop" in order to restore the previous matrix state

      // Repeat the same thing, only branch off to the "left" this time!
      ofPushMatrix();
      ofRotate(-theta);
      branch(len);
      ofPopMatrix();
   }
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
