#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    drawTunnel(ofGetFrameNum()*3, 0,0,500,500,ofColor(200,0,0), ofColor(0,0,100));
}

//--------------------------------------------------------------
void ofApp::drawTunnel(float phase, int locX, int locY, int width, int height, ofColor c1, ofColor c2){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(locX + width/2, locY + height/2);
    int totalSquares = 10;
    float maxDiff = width/totalSquares;
    float squareSpacingX = width/totalSquares;
    float squareSpacingY = height/totalSquares;

    for (int i = totalSquares; i>0; i--) {
      float tempPhase = phase + (i * 360/totalSquares);
      drawSquare(tempPhase, i * squareSpacingX, i * squareSpacingY, maxDiff, c1, c2);
    }
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawSquare(float phase, float width, float height, float maxDiff, ofColor c1, ofColor c2){
    ofPushStyle();
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(c1);
    ofDrawRectangle(0,0,width,height);
    ofSetColor(c2);
    float sizeDiff = maxDiff * (sin(ofDegToRad(phase))+1)/2 - 2;
    ofDrawRectangle(0,0,width-sizeDiff, height-sizeDiff);
    ofPopMatrix();
    ofPopStyle();
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
