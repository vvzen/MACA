#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    int initialSize = 50;

    for (int i = 0; i < initialSize; i++)
    {
        posX.push_back(ofGetWidth()/2);
        posY.push_back(ofGetHeight()/2);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    for (int i = 0; i < posX.size()-1; i++)
    {
        posX[i] = posX[i+1];
        posY[i] = posY[i+1];
    }
    posX[posX.size()-1] = mouseX;
    posY[posY.size()-1] = mouseY;
}

//--------------------------------------------------------------
void ofApp::draw(){

    for (int i = 0; i < posX.size()-1; i++)
    {
        float circleSize = ofMap(i, 0, posX.size()-1, 2, 30);
        ofColor red = ofColor(ofColor::red);
        ofColor yellow = ofColor(ofColor::yellow);
        float colorPc = ofMap(i, 0, posX.size()-1, 0, 1);
        ofSetColor(red.getLerped(yellow, colorPc));
        ofDrawCircle(posX[i], posY[i], circleSize);
    }
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
        posX.push_back(mouseX);
        posY.push_back(mouseY);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
