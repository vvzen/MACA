#include "MovementISource.h"

//--------------------------------------------------------------
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

    show_start_time = ofGetElapsedTimef();

    // used to keep timing in the intro
    intro_time_multiplier = 1;

    // start positions of the circles used in the checkpoint 3
    ellipse_1_pos = ofVec2f(fbo->getWidth()/8, fbo->getHeight()/2);
    ellipse_2_pos = ofVec2f(fbo->getWidth() * 7/8, fbo->getHeight()/2);
    // ellipse_2_pos = ofVec2f(fbo->getWidth()/8, fbo->getHeight()/2);
    // speeds of the ellipses
    ellipse_velocity = ofVec2f(0, 0);
    ellipse_acceleration= ofVec2f(0, 0.09);
    circles_size_multiplier = 1;
    bounce_count = 0;
}

//--------------------------------------------------------------
void MovementISource::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void MovementISource::update(){
    current_show_time = (ofGetElapsedTimef() - show_start_time);
}

void MovementISource::reset(){
    // initialise time at the start of source
    show_start_time = ofGetElapsedTimeMillis();
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
    if (!CHECKPOINT_1){
        drawFlashingIntro(intro_time_multiplier);
    }
    else if (CHECKPOINT_1 && !CHECKPOINT_2){
        drawMovingLines(current_show_time);
    }
    else if (CHECKPOINT_2 && !CHECKPOINT_3){
        drawMovingCircles(current_show_time);
    }

    // ofEnableAlphaBlending();
    // reference_image.draw(0, 0);
    // ofDisableAlphaBlending();

    //if a certain amount of time has passed (in millis), do something (change color in this case)
    // if (ofGetElapsedTimeMillis() - show_start_time < 500) ballColor = ofColor(255,0,0);
    // else if (ofGetElapsedTimeMillis() - show_start_time < 1000) ballColor = ofColor(0,255,0);
    // else if (ofGetElapsedTimeMillis() - show_start_time < 1500) ballColor = ofColor(255);

    if (show_calibration_grid){
        drawCalibrationGrid(32);
    }

    cout << "current show time: " << current_show_time << endl;

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
    float checkpoints[7] = {4, 8, 10, 12, 14, 15, 17}; // seconds
    bool show_rects = true;

    float current_time = (ofGetElapsedTimef() - show_start_time);

    // change rect color based on current time
    if ((current_time > checkpoints[0] && current_time < checkpoints[1]) && (rectangle_triggers[0] == false)){
        time_multiplier = 2;
        rectangle_triggers[0] = true;
        // cout << "increased time:" << time_multiplier << "x" << endl;
    }
    else if ((current_time > checkpoints[1] && current_time < checkpoints[2]) && (rectangle_triggers[1] == false)){
        time_multiplier = 4;
        rectangle_triggers[1] = true;
        // cout << "increased time:" << time_multiplier << "x" << endl;
    }
    else if ((current_time >= checkpoints[2] && current_time < checkpoints[3]) && rectangle_triggers[2] == false){
        time_multiplier = 8;
        rectangle_triggers[2] = true;
        // cout << "increased time:" << time_multiplier << "x" << endl;
    }
    else if ((current_time >= checkpoints[3] && current_time < checkpoints[4]) && (rectangle_triggers[3] == false)){
        time_multiplier = 20;
        rectangle_triggers[3] = true;
        // cout << "increased time:" << time_multiplier << "x" << endl;
    }
    else if ((current_time >= checkpoints[4] && current_time < checkpoints[5]) && (rectangle_triggers[4] == false)){
        time_multiplier = 100;
        rectangle_triggers[4] = true;
        // cout << "increased time:" << time_multiplier << "x" << endl;
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
    else {
        CHECKPOINT_1 = true;
    }

    ofPopStyle();
}

//--------------------------------------------------------------
// 2
//--------------------------------------------------------------
void MovementISource::drawMovingLines(float currentShowTime){

    if (!lines_started){
        lines_start_time = currentShowTime;
        lines_started = true;
    }
    bool lines_reached_end = false;
    int num_of_lines = fbo->getWidth() / 20;
    float line_spacing = fbo->getWidth() / num_of_lines;

    ofPushStyle();

    float checkpoints[4] = {0, 0.1, 0.2, 0.3}; // seconds
    float lines_checkpoints[3] = {1, 2.5, 11};
    float rect_checkpoints[3] = {13, 14};
    float final_checkpoint = 24;

    // compute "local" time since the first time this function was called
    float current_time = currentShowTime - lines_start_time;
    // cout << "current show time:  " << currentShowTime << endl;
    // cout << "current local time: " << current_time << endl;

    // two flashes
    if ((current_time > checkpoints[0] && current_time < checkpoints[1]) ||
        (current_time > checkpoints[2] && current_time < checkpoints[3])){
        
        int num_of_lines = fbo->getWidth() / 20;

        int color;
        color = (int(current_time) % 20 == 0) ? 255 : 0; 
        ofSetColor(color);

        for (int i = 0; i < num_of_lines; i++){
            ofVec2f increment(i * fbo->getWidth() / num_of_lines, i * fbo->getHeight() / num_of_lines);
            // v
            ofDrawLine(increment.x, 0, increment.x, fbo->getHeight());
            // h
            ofDrawLine(0, increment.y, fbo->getWidth(), increment.y);
        }
    }
    // lines animation
    else if (current_time > lines_checkpoints[0] && current_time < lines_checkpoints[2]){

        ofSetLineWidth(2);
        ofSetColor(255);

        // growing lines + growing rectangles
        // vertical
        
        // float duration = 1.5f; // the length of a single line animation
        float time_multiplier = 0.15;

        for (int i = 0; i < fbo->getWidth(); i+=line_spacing){
            float time_offset = (i / line_spacing) * time_multiplier;
            ofVec2f start_pos(i, fbo->getHeight());
            ofVec2f end_pos(i, ofMap(current_time, lines_checkpoints[0] + time_offset, lines_checkpoints[1] + time_offset, fbo->getHeight(), 0, true));
            ofDrawLine(start_pos, end_pos);
        }

        // horizontal
        time_multiplier = 0.25;
        for (int i = 0; i < fbo->getHeight(); i+=line_spacing){
            float time_offset = (i / line_spacing) * time_multiplier;
            ofVec2f start_pos(0, i);
            ofVec2f end_pos(ofMap(current_time, lines_checkpoints[0] + time_offset, lines_checkpoints[1] + time_offset, 0, fbo->getWidth(), true), i);
            ofDrawLine(start_pos, end_pos);

            // if we are at the end of the animation
            if (i >= fbo->getHeight()-line_spacing && current_time >= (lines_checkpoints[1] + time_offset) + 1){
                lines_reached_end = true;
            }
        }
        if (lines_reached_end){

            // save start time
            if (!rects_started){
                rects_start_time = current_time;
                rects_started = true;
                // cout << "rect start time: " << rects_start_time << endl;
                // cout << "checkpoint 7:" << checkpoints[7] << endl;
            }
        }
    }
    // rects growing
    else if (current_time > lines_checkpoints[0] && current_time < rect_checkpoints[1] && rects_started){

        ofSetColor(255);
        ofFill();

        // flash lines in the background
        if (current_time < rect_checkpoints[0]){
            // vertical
            if (ofGetFrameNum() % 10 == 0){
                for (int i = 0; i < fbo->getWidth(); i+=line_spacing){
                    ofVec2f start_pos(i, fbo->getHeight());
                    ofVec2f end_pos(i, 0);
                    ofDrawLine(start_pos, end_pos);
                }
            }
            // horizontal
            if (ofGetFrameNum() % 20 == 0){
                for (int i = 0; i < fbo->getHeight(); i+=line_spacing){
                    ofVec2f start_pos(0, i);
                    ofVec2f end_pos(fbo->getWidth(), i);
                    ofDrawLine(start_pos, end_pos);
                }
            }
        }

        int target_horizontal_rects_num = fbo->getWidth() / 20;
        int target_vertical_rects_num = fbo->getHeight() / 20;
        int current_horizontal_rects_num = ofMap(current_time, rects_start_time, rects_start_time+2, 0, target_horizontal_rects_num);
        float rect_size = fbo->getWidth() / target_horizontal_rects_num;
        
        // forward animation
        for (int y = 0; y < target_vertical_rects_num*2; y+=2){
            for (int i = 0; i < current_horizontal_rects_num - y; i++){
                ofVec2f pos(i * rect_size, y * rect_size);
                ofDrawRectangle(pos.x, pos.y, rect_size, rect_size);
            }
        }
        // backward animation
        for (int y = 1; y < target_vertical_rects_num*2; y+=2){
            for (int i = 0; i < current_horizontal_rects_num - y; i++){
                ofVec2f pos((target_horizontal_rects_num - i) * rect_size, y * rect_size);
                ofDrawRectangle(pos.x, pos.y, rect_size, rect_size);
            }
        }
    }

    else if (current_time >= rect_checkpoints[1]){

        int colors[4] = {255, 255, 255, 255};

        colors[0] = (current_time > rect_checkpoints[1] + 1) == true ? 0 : 255;
        colors[1] = (current_time > rect_checkpoints[1] + 1.5) == true ? 0 : 255;
        colors[2] = (current_time > rect_checkpoints[1] + 2.0) == true ? 0 : 255;
        colors[3] = (current_time > rect_checkpoints[1] + 2.5) == true ? 0 : 255;

        ofVec2f size(fbo->getWidth(), fbo->getHeight());

        ofPushMatrix();
        
        ofTranslate(fbo->getWidth()/2, fbo->getHeight()/2);

        float scale_factor = ofMap(current_time, rect_checkpoints[1] + 1, rect_checkpoints[1] + 2, 1, 0.01, true);
        ofScale(1, scale_factor, 1);

        ofDrawRectangle(-size.x/2, -size.y/2, size.x, size.y);

        cout << "scale factor: " << scale_factor << endl;

        if (scale_factor <= 0.02){
            CHECKPOINT_2 = true;
        }
        
        ofPopMatrix();
    }
    
    ofPopStyle();
}

//--------------------------------------------------------------
// 3
//--------------------------------------------------------------
void MovementISource::drawMovingCircles(float currentShowTime){
    
    // save the start time
    if (!bars_started){
        bars_start_time = currentShowTime;
        bars_started = true;
    }

    // compute "local" time since the first time this function was called
    float current_time = currentShowTime - bars_start_time;
    float checkpoints[5] = {0, 1, 3, 25, 30};
    
    ofPushStyle();

    // do different things based on current time
    // scale and rotate the square 
    if (current_time > checkpoints[0] && current_time < checkpoints[1]){
        ofPushMatrix();
        ofTranslate(fbo->getWidth()/2, fbo->getHeight()/2);
        
        ofRotateZ(ofMap(current_time, checkpoints[0], checkpoints[1], 0, 90, true));
        ofScale(1, 0.02, 1);
        
        ofVec2f size(fbo->getWidth(), fbo->getHeight());

        ofDrawRectangle(-size.x/2, -size.y/2, size.x, size.y);
        ofPopMatrix();
    }
    // bounce the balls
    else if (current_time > checkpoints[1] && current_time < checkpoints[3]){

        ofPushMatrix();
        ofTranslate(fbo->getWidth()/2, fbo->getHeight()/2);
        ofSetCircleResolution(50);
        
        // replicate the center rectangle that we left in the previous checkpoint
        ofRotateZ(90);
        // animate the scale
        float scale_factor = ofMap(current_time, checkpoints[1], checkpoints[2], 0.01, 0.85, true);
        ofScale(1, scale_factor, 1);
        
        ofVec2f size(fbo->getWidth(), fbo->getHeight());

        ofDrawRectangle(-size.x/2, -size.y/2, size.x, size.y);
        ofPopMatrix();

        // animate the size the of the circles
        float circles_size = ofMap(scale_factor, 0.01, 0.85, 1, 40);
        circles_size *= circles_size_multiplier;

        // after they've appeared, make the two circles bounce!
        // at each bounce, their radius gets smaller
        // at each bounce, we reveal the other circle
        if (current_time > checkpoints[2]){

            // these variables have class scope! see setup()
            ellipse_velocity += ellipse_acceleration;
            ellipse_velocity.limit(9);
            ellipse_1_pos += ellipse_velocity;
            ellipse_2_pos += ellipse_velocity;

            if (ellipse_1_pos.y > fbo->getHeight() - circles_size) {
                ellipse_velocity.y *= -0.95;
                show_left_ellipse = !show_left_ellipse;
                circles_size_multiplier -= 0.1;
                bounce_count++;
            }
            // else if (ellipse_1_pos.y < circles_size / 2){
            //     ellipse_velocity.y *= -0.95;
            //     show_left_ellipse = !show_left_ellipse;
            // }
        }
        // show only one ball at a time
        int color_1;
        int color_2;
        if (bounce_count < 10){
            ofPushMatrix();
                ofTranslate(ellipse_1_pos.x, ellipse_1_pos.y, 0);
                color_1 = (show_left_ellipse == true) ? 255 : 0;
                ofSetColor(color_1);
                ofDrawCircle(0, 0, circles_size, circles_size);
            ofPopMatrix();
            ofPushMatrix();
                color_2 = (show_left_ellipse == true) ? 0 : 255;
                ofSetColor(color_2);
                ofTranslate(ellipse_2_pos.x, ellipse_2_pos.y, 0);
                ofDrawCircle(0, 0, circles_size, circles_size);
            ofPopMatrix();
        }
    }
    else if (current_time > checkpoints[3] && current_time < checkpoints[4]){
        // replicate the center rectangle that we left in the previous checkpoint
        ofPushMatrix();
        ofDrawRectangle(fbo->getWidth()/4, 0, fbo->getWidth()/2, fbo->getHeight());
        ofPopMatrix();
    }
    ofPopStyle();
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