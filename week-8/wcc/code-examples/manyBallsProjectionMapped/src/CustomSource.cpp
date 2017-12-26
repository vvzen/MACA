#include "CustomSource.h"

void CustomSource::setup(){
	// Give our source a decent name
    name = "Custom FBO Source";

	// Allocate our FBO source, decide how big it should be
    allocate(1000, 500);

    setupBalls();
}

void CustomSource::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void CustomSource::update(){
    updateBalls();
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void CustomSource::draw(){
    ofClear(0); //clear the buffer
    drawBalls(0,0,fbo->getWidth(), fbo->getHeight()); // Fill FBO with RED balls
}

//================================================================
void CustomSource::setupBalls() {
    ofSetCircleResolution(50);
    for (int i=0; i<50; i++){
        ofVec2f randomLocation = ofVec2f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
        locations.push_back(randomLocation);
        ofVec2f randomSpeed = ofVec2f(ofRandom(-3,3),ofRandom(-3,3));
        speeds.push_back(randomSpeed);
    }
}

void CustomSource::updateBalls(){
    // Move balls
    for(int i = 0; i < locations.size(); i++){
        locations[i] = locations[i] + speeds[i];
        if (locations[i].x<5 || locations[i].x>fbo->getWidth()-5) speeds[i].x*=-1;
        if (locations[i].y<5 || locations[i].y>fbo->getHeight()-5) speeds[i].y*=-1;
    }
}

void CustomSource::drawBalls(int x, int y, int w, int h){
    ofSetColor(255);
    for(int i = 0; i < locations.size(); i++){     
        ofDrawCircle(locations[i], 5);
    }
}
