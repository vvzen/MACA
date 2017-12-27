#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    posX = 50;
    posY = ofGetHeight()/2;
    ofBackground(0);
    stepX = 3;
    stepY = 4;
    ballRad = 10;
}

//--------------------------------------------------------------
void ofApp::update(){
    posX = posX + stepX;
    posY = posY + stepY;

    if (posX>ofGetWidth()-ballRad || posX<0+ballRad){
        stepX = stepX * -1;
    }
    if (posY>ofGetHeight()-ballRad || posY<0+ballRad){
        stepY = stepY * -1;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawCircle(posX, posY, ballRad);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
