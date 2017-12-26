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
    movingRect(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(), ofGetHeight(), ofColor(255,0,0));
}

void ofApp::movingRect(int x, int y, int w, int h, ofColor c){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(c);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofTranslate(x,y);
    float phase = sin(ofDegToRad(ofGetFrameNum()*2));
    float s = ofMap(phase, -1, 1, 0.2, 1);
    ofScale(s,s,1);
    ofDrawRectangle(0,0,w,h);
    ofPopStyle();
    ofPopMatrix();
}
