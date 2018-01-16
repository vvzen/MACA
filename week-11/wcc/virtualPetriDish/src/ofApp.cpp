#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(125);
    ballSys.setup(15);
}

//--------------------------------------------------------------
void ofApp::update(){
    ballSys.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ballSys.draw();
    ofDrawBitmapString("Total Agents: " + ofToString(ballSys.balls.size()), 10, 20);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    ballSys.infectBall(x,y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}
