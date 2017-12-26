#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

    ofSetCircleResolution(50);

    for (int i=0; i<50; i++){
        ofVec2f randomLocation = ofVec2f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
        locations.push_back(randomLocation);
        ofVec2f randomSpeed = ofVec2f(ofRandom(-3,3),ofRandom(-3,3));
        speeds.push_back(randomSpeed);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // Move balls
    for(int i = 0; i < locations.size(); i++){
        locations[i] = locations[i] + speeds[i];
        if (locations[i].x<5 || locations[i].x>ofGetWidth()-5) speeds[i].x*=-1;
        if (locations[i].y<5 || locations[i].y>ofGetHeight()-5) speeds[i].y*=-1;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw balls
    ofSetColor(255);
    for(int i = 0; i < locations.size(); i++){
        ofDrawCircle(locations[i], 5);
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
