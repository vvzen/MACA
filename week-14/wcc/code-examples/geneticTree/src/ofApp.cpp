#include "ofApp.h"
#define FRAME_WIDTH 80
#define FRAME_HEIGHT 60
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    popmax = 10;
    mutationRate = 0.025;
    forrest.setup(mutationRate, popmax);
}
//--------------------------------------------------------------
void ofApp::update(){
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth()/20, ofGetHeight()-30);
    forrest.draw();
}
//--------------------------------------------------------------
void ofApp::displayInfo(){

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'g' || key == 'G') {
        forrest.selection();
        forrest.generate();
    }
    else if (key>=48 || key <=57 ) {
        forrest.pick(ofToInt(ofToString(char(key))));
    }
}
