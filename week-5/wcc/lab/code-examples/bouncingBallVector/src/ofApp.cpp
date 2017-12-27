#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    for (int i=0; i<100; i++)
    {
        posX.push_back(ofRandom(ofGetWidth()));
        posY.push_back(ofRandom(ofGetHeight()));
        stepX.push_back(ofRandom(-4,4));
        stepY.push_back(ofRandom(-4,4));
        ballRad.push_back(ofRandom(2,6));
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    for (int i = 0; i < stepX.size(); i++)
    {
        posX[i] = posX[i] + stepX[i];
        posY[i] = posY[i] + stepY[i];

        if (posX[i]>ofGetWidth()-ballRad[i] || posX[i]<0+ballRad[i]){
            stepX[i] = stepX[i] * -1;
        }
        if (posY[i]>ofGetHeight()-ballRad[i] || posY[i]<0+ballRad[i]){
            stepY[i] = stepY[i] * -1;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < stepX.size(); i++)
    {
        ofDrawCircle(posX[i], posY[i], ballRad[i]);
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
    stepX.push_back(ofRandom(-5,5));
    stepY.push_back(ofRandom(-5,5));
    ballRad.push_back(ofRandom(3, 8));
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
