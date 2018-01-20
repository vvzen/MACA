#include "FunkyTriangle.h"

//--------------------------------------------------------------
void FunkyTriangle::setup(ofPoint p1, ofPoint p2, ofPoint p3){

    color = ofColor(0);
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    color_seed = ofRandom(0, 1000);
}

//--------------------------------------------------------------
void FunkyTriangle::update(){

    float brightness = ofMap(sin(ofGetElapsedTimef() + color_seed), -1, 1, 0, 255);
    color.setBrightness(brightness);
}

//--------------------------------------------------------------
void FunkyTriangle::draw(){
    
    ofPushStyle();
    ofSetColor(color);
    ofDrawTriangle(points[0], points[1], points[2]);
    ofPopStyle();
}