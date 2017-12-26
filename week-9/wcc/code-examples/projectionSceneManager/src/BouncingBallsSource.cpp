#include "BouncingBallsSource.h"

void BouncingBallsSource::setup(){
	// Give our source a decent name
    name = "Bouncing Balls FBO Source";

	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);

    setupBalls();    
}

void BouncingBallsSource::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void BouncingBallsSource::update(){
    updateBalls();
}

void BouncingBallsSource::reset(){
    //initialise time at the start of source
    startTime = ofGetElapsedTimeMillis();
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void BouncingBallsSource::draw(){
    ofPushStyle();

    ofClear(0); //clear the buffer

    //if a certain amount of time has passed (in millis), do something (change color in this case)
    if (ofGetElapsedTimeMillis() - startTime < 500) ballColor = ofColor(255,0,0);
    else if (ofGetElapsedTimeMillis() - startTime < 1000) ballColor = ofColor(0,255,0);
    else if (ofGetElapsedTimeMillis() - startTime < 1500) ballColor = ofColor(255);

    //something happening every 60 frames using modulo
//    if (ofGetFrameNum()%60==0) {
//        ballColor = ofColor(ofRandom(0, 255),ofRandom(0,255),ofRandom(0,255));
//    }

    drawBalls(0,0,fbo->getWidth(), fbo->getHeight()); // Fill FBO with RED balls

    ofPopStyle();
}

//================================================================
void BouncingBallsSource::setupBalls() {
    ofSetCircleResolution(50);
    for (int i=0; i<50; i++){
        ofVec2f randomLocation = ofVec2f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
        locations.push_back(randomLocation);
        ofVec2f randomSpeed = ofVec2f(ofRandom(-3,3),ofRandom(-3,3));
        speeds.push_back(randomSpeed);
    }
}

void BouncingBallsSource::updateBalls(){
    // Move balls
    for(int i = 0; i < locations.size(); i++){
        locations[i] = locations[i] + speeds[i];
        if (locations[i].x<5 || locations[i].x>fbo->getWidth()-5) speeds[i].x*=-1;
        if (locations[i].y<5 || locations[i].y>fbo->getHeight()-5) speeds[i].y*=-1;
    }
}

void BouncingBallsSource::drawBalls(int x, int y, int w, int h){
    ofSetColor(ballColor);
    for(int i = 0; i < locations.size(); i++){     
        ofDrawCircle(locations[i], 5);
    }
}
