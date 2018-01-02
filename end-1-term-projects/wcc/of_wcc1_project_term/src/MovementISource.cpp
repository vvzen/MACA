#include "MovementISource.h"

void MovementISource::setup(){
	// Give our source a decent name
    name = "Movement 1 Source";

	// Allocate our FBO source, decide how big it should be
    allocate(990, 585);
    // this->allocate(990, 585, GL_RGBA, 8)

    // if you want to draw something inside setup you need to make calls to this->beginFbo() / this->endFbo as below
    this->beginFbo();
        ofClear(255,0,0);
    this->endFbo();

    // reference_image.allocate(990, 585, OF_IMAGE_COLOR_ALPHA);
    reference_image.load("accordion_reference_matching_bg.png");

    start_time = ofGetElapsedTimef();

    // used to keep timing in the
    intro_time_multiplier = 1;
}

void MovementISource::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void MovementISource::update(){
    
}

void MovementISource::reset(){
    // initialise time at the start of source
    start_time = ofGetElapsedTimeMillis();
    ofClear(0); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void MovementISource::draw(){

    ofPushStyle();
    ofClear(0); // remove if you never want to update the background
    // ofBackground(0);

    ofSetCircleResolution(20);
    // ofSetLineWidth(3);
    ofFill();

    // draw flashing intro rectangles
    drawFlashingIntro(intro_time_multiplier);

    ofSetColor(255, 0, 0);
    ofDrawCircle(fbo->getWidth()/2, fbo->getHeight()/2, 10, 10);

    // ofVec2f tris_pos(fbo->getWidth()/2, fbo->getHeight()/2);
    // ofDrawTriangle(tris_pos.x, tris_pos.y, tris_pos.x + 55, tris_pos.y - 50, tris_pos.x - 55, tris_pos.y - 50);

    // ofEnableAlphaBlending();
    // reference_image.draw(0, 0);
    // ofDisableAlphaBlending();

    //if a certain amount of time has passed (in millis), do something (change color in this case)
    // if (ofGetElapsedTimeMillis() - start_time < 500) ballColor = ofColor(255,0,0);
    // else if (ofGetElapsedTimeMillis() - start_time < 1000) ballColor = ofColor(0,255,0);
    // else if (ofGetElapsedTimeMillis() - start_time < 1500) ballColor = ofColor(255);

    if (show_calibration_grid){
        drawCalibrationGrid(32);
    }

    ofPopStyle();
}
//--------------------------------------------------------------
// 0
// draw a grid, useful for calibration
//--------------------------------------------------------------
void MovementISource::drawCalibrationGrid(int numOfLines){
    
    for (int i = 0; i < numOfLines; i++){
        ofVec2f increment(i * fbo->getWidth() / numOfLines, i * fbo->getHeight() / numOfLines);
        ofSetColor(0, 255, 0);
        // v
        ofDrawLine(increment.x, 0, increment.x, fbo->getHeight());
        // h
        ofDrawLine(0, increment.y, fbo->getWidth(), increment.y);
        ofSetColor(255, 0, 0);
    }
}

//--------------------------------------------------------------
// 1
//--------------------------------------------------------------
void MovementISource::drawFlashingIntro(int & time_multiplier){

    ofPushStyle();

    int colors[] = {0, 0, 0, 0};
    float checkpoints[7] = {4, 8, 10, 12, 14, 15, 17};
    bool show_rects = true;

    float current_time = (ofGetElapsedTimef() - start_time);

    // cout << "current_time: " << current_time << endl;
    // cout << "time_multiplier: " << time_multiplier << endl;
    // cout << "rectangle_triggers[0]: " << rectangle_triggers[0] << endl;

    if ((current_time > checkpoints[0] && current_time < checkpoints[1]) && (rectangle_triggers[0] == false)){
        time_multiplier = 2;
        rectangle_triggers[0] = true;
        cout << "increased time: 2x" << endl;
    }
    else if ((current_time > checkpoints[1] && current_time < checkpoints[2]) && (rectangle_triggers[1] == false)){
        time_multiplier = 4;
        rectangle_triggers[1] = true;
        cout << "increased time: 4x" << endl;
    }
    else if ((current_time >= checkpoints[2] && current_time < checkpoints[3]) && rectangle_triggers[2] == false){
        time_multiplier = 8;
        rectangle_triggers[2] = true;
        cout << "increased time: 8x" << endl;
    }
    else if ((current_time >= checkpoints[3] && current_time < checkpoints[4]) && (rectangle_triggers[3] == false)){
        time_multiplier = 20;
        rectangle_triggers[3] = true;
        cout << "increased time: 20x" << endl;
    }
    else if ((current_time >= checkpoints[4] && current_time < checkpoints[5]) && (rectangle_triggers[4] == false)){
        time_multiplier = 100;
        rectangle_triggers[4] = true;
        cout << "increased time: 32x" << endl;
    }
    else if (current_time >= checkpoints[6] && rectangle_triggers[5] == false){
        show_rects = false;
    }
    
    if (show_rects){

        ofVec2f size(fbo->getWidth()/4, fbo->getHeight());
        ofVec2f pos(0, 0);
        
        current_time *= time_multiplier;
        
        colors[0] = (int(current_time) % 4 == 0) ? 255 : 0;
        colors[1] = (int(current_time) % 4 == 1) ? 255 : 0;
        colors[2] = (int(current_time) % 4 == 2) ? 255 : 0;
        colors[3] = (int(current_time) % 4 == 3) ? 255 : 0;
        
        ofSetColor(colors[0]);
        ofDrawRectangle(pos.x, pos.y, size.x, size.y);

        ofSetColor(colors[1]);
        ofDrawRectangle(1 * size.x, pos.y, size.x, size.y);

        ofSetColor(colors[2]);
        ofDrawRectangle(2 * size.x, pos.y, size.x, size.y);

        ofSetColor(colors[3]);
        ofDrawRectangle(3 * size.x, pos.y, size.x, size.y);
    }

    ofPopStyle();
}

//--------------------------------------------------------------
// 2
//--------------------------------------------------------------
void MovementISource::drawMovingLines(){
    
}

//--------------------------------------------------------------
// EVENTS
//--------------------------------------------------------------
void MovementISource::onKeyPressed(ofKeyEventArgs & event){
    switch (event.key){
        case 'd': {
            show_calibration_grid = !show_calibration_grid;
        }
    }
}