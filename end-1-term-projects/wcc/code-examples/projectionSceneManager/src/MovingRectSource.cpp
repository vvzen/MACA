#include "MovingRectSource.h"

void MovingRectSource::setup(){
	// Give our source a decent name
    name = "Moving Rect FBO Source";
    rectColor = ofColor(255);
	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);
}

void MovingRectSource::reset(){
    //reset is called optionally. if you leave it empty nothing is happening
    rectColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

void MovingRectSource::setName(string _name){
    name = _name;
}

void MovingRectSource::setColor(ofColor c){
    rectColor = c;
}

// Don't do any drawing here
void MovingRectSource::update(){
     time = ofGetFrameNum()*2;
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void MovingRectSource::draw(){
    ofClear(0); //clear the buffer

    //do it with static values
    //since the buffer is 500x500, then...
    //drawMovingRect(250, 250, 500, 500);

    //or pass it dynamic values (ie. ask the fbo how big it is)
    drawMovingRect(fbo->getWidth()/2, fbo->getHeight()/2, fbo->getWidth(), fbo->getHeight(), time);
}

void MovingRectSource::drawMovingRect(int x, int y, int w, int h, float time){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(rectColor);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofTranslate(x,y);
    float phase = sin(ofDegToRad(time));
    float s = ofMap(phase, -1, 1, 0.2, 1);
    ofScale(s,s,1);
    ofDrawRectangle(0,0,w,h);
    ofPopStyle();
    ofPopMatrix();
}
