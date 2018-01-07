#include "MovementISource.h"

//--------------------------------------------------------------
void MovementISource::init_vars(){

    // initialise time at the start of source
    show_start_time = ofGetElapsedTimef();

    // reference_image.allocate(990, 585, OF_IMAGE_COLOR_ALPHA);
    reference_image.load("accordion_reference_matching_bg.png");

    // used to keep timing in the intro
    intro_time_multiplier = 1;

    // start positions of the circles used in the checkpoint 3
    ellipse_1_pos = ofVec2f(fbo->getWidth()/8, fbo->getHeight()/2);
    ellipse_2_pos = ofVec2f(fbo->getWidth() * 7/8, fbo->getHeight()/2);
    
    CHECKPOINT_1 = true;    

    // checkpoint 2
    CHECKPOINT_2 = true;
    lines_started = false;
    rects_started = false;

    // checkpoint 3
    // speeds of the ellipses
    // ellipse_velocity = ofVec2f(0, 0);
    // ellipse_acceleration= ofVec2f(0, 0.09);
    // circles_size_multiplier = 1;
    // bounce_count = 0;
    center_rect_size = ofVec2f(fbo->getWidth(), fbo->getHeight());
    CHECKPOINT_3 = false;
    bars_started = false;
    show_left_ellipse = false;
    ball_disappeared = false;
    quads_started = false;
    quads_ended = false;
    quads_started = false;
    // find the biggest quad that if tiled covers the a 1/4 of the fbo
    quad_size = find_max_square_to_evenly_fit_rect(int(fbo->getWidth() / 4), int(fbo->getHeight()));

    // checkpoint 4
    CHECKPOINT_4 = false;
    num_rects_h_1 = 0;
    num_rects_h_2 = 0;
    num_rects_h_3 = 0;
    num_rects_h_4 = 0;
    bg_started_fade = false;
    coloured_lines_started = false;
}

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

    init_vars();
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
    ofClear(0); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
    init_vars();
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
    // moving lines and quads
    else if (CHECKPOINT_1 && !CHECKPOINT_2){
        drawMovingLines(current_show_time);
    }
    // bouncing circle and change of 2D plane
    else if (CHECKPOINT_2 && !CHECKPOINT_3){
        drawMovingCircles(current_show_time);
    }
    // colors!
    else if (CHECKPOINT_3 && !CHECKPOINT_4){
        drawColouredLines(current_show_time);
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

        ofSetColor(255);

        // growing lines + growing rectangles
        // vertical
        float time_multiplier = 0.15;

        float lines_width;

        for (int i = 0; i < fbo->getWidth(); i+=line_spacing){
            float time_offset = (i / line_spacing) * time_multiplier;
            // set width
            lines_width = ofMap(i, 0, fbo->getWidth(), 1, 7, true);
            ofSetLineWidth(lines_width);
            ofVec2f start_pos(i, fbo->getHeight());
            ofVec2f end_pos(i, ofMap(current_time, lines_checkpoints[0] + time_offset, lines_checkpoints[1] + time_offset, fbo->getHeight(), 0, true));
            ofDrawLine(start_pos, end_pos);
        }

        // horizontal
        time_multiplier = 0.25;
        for (int i = 0; i < fbo->getHeight(); i+=line_spacing){
            float time_offset = (i / line_spacing) * time_multiplier;
            // set width
            lines_width = ofMap(i, 0, fbo->getHeight(), 7, 1, true);
            ofSetLineWidth(lines_width);
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
                ofSetLineWidth(2);
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
    // final rect animation with scale shrinking
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

        // cout << "scale factor: " << scale_factor << endl;

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
    float checkpoints[4] = {0, 1, 3, 22};
    float lines_checkpoints[7] = {22, 24, 26, 28, 36, 40, 50};
    
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
    else if (current_time > checkpoints[1] && current_time < checkpoints[3] && !ball_disappeared){

        ofPushMatrix();
        ofTranslate(fbo->getWidth()/2, fbo->getHeight()/2);
        ofSetCircleResolution(50);
        
        // replicate the center rectangle that we left in the previous checkpoint
        ofRotateZ(90);
        // animate the scale
        float scale_factor = ofMap(current_time, checkpoints[1], checkpoints[2], 0.01, 0.85, true);
        ofScale(1, scale_factor, 1);

        ofDrawRectangle(-center_rect_size.x/2, -center_rect_size.y/2, center_rect_size.x, center_rect_size.y);
        ofPopMatrix();

        // when the center animation is finished, start the quads one
        if (scale_factor >= 0.85 && !quads_started){
            quads_started = true;
            quads_start_time = current_time;
        }

        // TODO: center panels: dissolve quads

        float quads_color;
        float time_offset = 0.0f;
        float duration = 0.8f;
        int num_x_quads = fbo->getWidth()/4 / quad_size;
        int num_y_quads = fbo->getHeight() / quad_size;

        ofPushMatrix();
        
        // slowly fade in + rotation of the quads
        // draw them on first panel from the left and first from the right
        // repeat until animation is done
        if (quads_started && !quads_ended){
                
            // LEFT PANEL
            for (int x = 0; x < fbo->getWidth()/4; x+=quad_size){
                for (int y = fbo->getHeight(); y >= 0; y-=quad_size){
                    
                    float y_time_shift = ofMap(y, fbo->getHeight(), 0, 0, fbo->getHeight());
                    time_offset = (x * 0.004) + (y_time_shift * 0.008);
                    // animate color, scale, rotation
                    float start_time = quads_start_time + time_offset;
                    float end_time = quads_start_time + time_offset + duration;
                    float end_time_color = quads_start_time + time_offset + (duration * 1.3);

                    quads_color = ofMap(current_time, start_time, end_time_color, 0, 255, true);
                    float scale_animated = ofMap(current_time, start_time, end_time, 0.001, 1, true);
                    float rotation_animated = ofMap(current_time, start_time, end_time, 90, 0, true);

                    ofPushMatrix();
                    ofTranslate(x, y, 0);
                    ofRotateX(rotation_animated);

                    ofSetColor(quads_color);
                    ofDrawRectangle(-quad_size, 0, quad_size * scale_animated, quad_size * scale_animated);

                    // check when we're done
                    if (x >= fbo->getWidth()/4 - quad_size && y <= quad_size){
                        if (quads_color == 255 && scale_animated == 1 && rotation_animated == 0){
                            quads_ended = true;
                        }
                    }
                    ofPopMatrix();
                }
            }
            
            time_offset = 0;

            // move to the other panel
            ofTranslate(fbo->getWidth() * 3/4, 0, 0);
            // RIGHT PANEL
            for (int x = fbo->getWidth()/4; x >= 0; x-=quad_size){
                for (int y = fbo->getHeight(); y >= 0; y-=quad_size){
                    
                    // make quads appear slowly from bottom right
                    float y_time_shift = ofMap(y, fbo->getHeight(), 0, 0, fbo->getHeight());
                    float x_time_shift = ofMap(x, fbo->getWidth()/4, 0, 0, fbo->getWidth()/4);
                    time_offset = (x_time_shift * 0.004) + (y_time_shift * 0.008);
                    // animate color, scale, rotation
                    quads_color = ofMap(current_time, quads_start_time + time_offset, quads_start_time + time_offset + (duration * 1.3), 0, 255, true);
                    float scale_animated = ofMap(current_time, quads_start_time + time_offset, quads_start_time + time_offset + duration, 0.001, 1, true);
                    float rotation_animated = ofMap(current_time, quads_start_time + time_offset, quads_start_time + time_offset + duration, 90, 0, true);

                    ofPushMatrix();
                    ofTranslate(x, y, 0);
                    ofRotateX(rotation_animated);

                    ofSetColor(quads_color);
                    ofDrawRectangle(0, 0, quad_size * scale_animated, quad_size * scale_animated);

                    ofPopMatrix();
                }
            }
        }

        if (quads_ended){
            cout << "elapsed time: " << current_time - quads_start_time << endl;
        }

        ofPopMatrix();
    }
    else if (quads_ended && current_time > lines_checkpoints[0] && current_time < lines_checkpoints[6]){

        ofSetLineWidth(8);
        ofDrawLine(0, fbo->getHeight(), 0, 0);
        // animate lines coming up from the bottom
        float animated_y_head = ofMap(current_time, lines_checkpoints[0], lines_checkpoints[1], fbo->getHeight(), 0, true);
        float animated_y_tail = fbo->getHeight();

        // break the 2D barriers! rotate around X axis
        if (current_time >= lines_checkpoints[2]){
            float rotate_amount = ofMap(current_time, lines_checkpoints[2], lines_checkpoints[3], 0, 86, true);
            float move_amount = ofMap(current_time, lines_checkpoints[2], lines_checkpoints[3], 0, fbo->getHeight()/2, true);
            ofTranslate(0, move_amount, 0);
            ofRotateX(rotate_amount);
            // animate lines growing on the fake z axis
            if (current_time >= lines_checkpoints[3]){
                float time_offset = 1;
                animated_y_head = ofMap(current_time, lines_checkpoints[3] + time_offset, lines_checkpoints[4] + time_offset, 0, -fbo->getHeight()*1000, true);
                animated_y_tail = ofMap(current_time, lines_checkpoints[3] + time_offset, lines_checkpoints[4] + time_offset, fbo->getHeight(), -fbo->getHeight()*100, true);
            }
        }
        // draw the lines
        int num_of_lines = 32;
        float line_spacing_x = fbo->getWidth() / num_of_lines;
        for (int i = 0; i < num_of_lines; i++){
            ofDrawLine(i * line_spacing_x, animated_y_tail, i * line_spacing_x, animated_y_head);
        }

        if(animated_y_tail < -10000){
            CHECKPOINT_3 = true;
        }
    }
    ofPopStyle();
}

//--------------------------------------------------------------
// 4
//--------------------------------------------------------------
void MovementISource::drawColouredLines(float currentShowTime){

    // save the start time
    if (!coloured_lines_started){
        coloured_lines_start_time = currentShowTime;
        coloured_lines_started = true;
    }
    // useful for keeping time, like keyframes
    // float checkpoints[2] = {0, 32};

    // compute "local" time since the first time this function was called
    float current_time = currentShowTime - coloured_lines_start_time;

    ofPushStyle();

    // max vertical size of the rectangles
    
    float max_x_rect_size = 6;
    float max_y_rect_size = 12;
    float size_x;
    float size_y;
    // int lines_x_step = (fbo->getWidth() / 4) / max_x_rect_size;
    int lines_y_step = fbo->getHeight() / max_y_rect_size;

    // colors
    float saturation = 50;
    float hue;
    float darkness = 198;
    ofColor color;

    ofPushMatrix();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    // slowly add more rectangles
    if (ofGetFrameNum() % 60 == 0) num_rects_h_1++;
    if (num_rects_h_1 > 10 && ofGetFrameNum() % 40 == 1) num_rects_h_2++;
    if (num_rects_h_2 > 10 && ofGetFrameNum() % 30 == 0) num_rects_h_3++;
    if (num_rects_h_3 > 10 && ofGetFrameNum() % 20 == 0) num_rects_h_4++;

    ofPushMatrix();

    // draw different coloured lines
    // horizontal
    if (current_time > 0){
        for (int i = 0; i < num_rects_h_1; i++){
            // size
            size_x = fbo->getWidth()/4;
            size_y = ofMap(ofSignedNoise(i, current_time*3), -1, 1, 2, max_y_rect_size);
            // colors
            hue = ofMap(i * lines_y_step, 0, fbo->getHeight(), 0, 255);
            color.setHsb(hue, saturation, darkness, 255);
            ofSetColor(color);
            // ofDrawRectangle(0, i * lines_y_step + (sin(ofSignedNoise(current_time * 0.005)) * 20), size_x, size_y);
            ofDrawRectangle(0, i * lines_y_step + (sin(ofSignedNoise(i, current_time)) * 10), size_x, size_y);
        }
    }
    if (num_rects_h_1 > 0){
        // increase saturation
            saturation *= 2;
            // increase vertical size of the rectangles
            max_y_rect_size *= 2;
            ofTranslate(fbo->getWidth()/4, 0, 0);
        for (int i = num_rects_h_2; i > 0; i--){
            // size
            size_x = fbo->getWidth()/4;
            size_y = ofMap(ofSignedNoise(i, current_time*3), -1, 1, 2, max_y_rect_size);
            // colors
            hue = ofMap(i * lines_y_step, 0, fbo->getHeight(), 0, 255);
            color.setHsb(hue, saturation, darkness, 255);
            ofSetColor(color);
            ofDrawRectangle(0, i * lines_y_step + (sin(ofSignedNoise(i+2, current_time)) * 20), size_x, size_y);
        }
    }
    if (num_rects_h_2 > 0){
        // increase saturation
        saturation *= 2;
        // increase vertical size of the rectangles
        max_y_rect_size *= 2;
        ofTranslate(fbo->getWidth()/4, 0, 0);
        for (int i = 0; i < num_rects_h_3; i++){
            // size
            size_x = fbo->getWidth()/4;
            size_y = ofMap(ofSignedNoise(i, current_time*3), -1, 1, 2, max_y_rect_size);
            // colors
            hue = ofMap(i * lines_y_step, 0, fbo->getHeight(), 0, 255);
            color.setHsb(hue, saturation, darkness, 255);
            ofSetColor(color);
            ofDrawRectangle(0, i * lines_y_step + (sin(ofSignedNoise(i-1, current_time)) * 30), size_x, size_y);
        }
    }
    if (num_rects_h_3 > 0){
        // increase saturation
        saturation *= 2;
        // increase vertical size of the rectangles
        max_y_rect_size *= 2;
        ofTranslate(fbo->getWidth()/4, 0, 0);
        for (int i = num_rects_h_4; i > 0; i--){
            // size
            size_x = fbo->getWidth()/4;
            size_y = ofMap(ofSignedNoise(i, current_time*3), -1, 1, 2, max_y_rect_size);
            // colors
            hue = ofMap(i * lines_y_step, 0, fbo->getHeight(), 0, 255);
            color.setHsb(hue, saturation, darkness, 255);
            ofSetColor(color);
            ofDrawRectangle(0, i * lines_y_step + (sin(ofSignedNoise(i-1, current_time)) * 40), size_x, size_y);
        }
    }
    ofPopMatrix();
    ofDisableBlendMode();

    ofEnableAlphaBlending();

    // slowly fade in a rect from the background
    if (num_rects_h_4 > 10 && !bg_started_fade){
        white_bg_fade_in_time = current_time;
        bg_started_fade = true;
    }
    if (bg_started_fade){
        float duration = 6;
        float animated_alpha = ofMap(current_time, white_bg_fade_in_time, white_bg_fade_in_time + duration, 0, 255, true);
        ofColor center_color(255, 255, 255, animated_alpha);
        ofColor sides_color(0, 0, 0, animated_alpha);
        ofSetColor(center_color);
        ofDrawRectangle(fbo->getWidth()/4, 0, fbo->getWidth()/2, fbo->getHeight());
        
        ofSetColor(sides_color);
        ofDrawRectangle(0, 0, fbo->getWidth()/4, fbo->getHeight());
        ofDrawRectangle(fbo->getWidth()*3/4, 0, fbo->getWidth()/4, fbo->getHeight());
    }

    ofDisableAlphaBlending();

    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
// MATHS
//--------------------------------------------------------------
// this algorithm takes a width and a height and returns
// the length of the side of the biggest square that can be repeated
// in order to fill up the width x height rectangle evenly
// 
//  __ __ __
// |__|__|__|
// |__|__|LL| <-- this 1x1 square is the biggest one able to fill this 3x2 rectangle evenly
 
int MovementISource::find_max_square_to_evenly_fit_rect(int w, int h){

    // DIVIDE AND CONQUER
    // 1. we do this only at the start: get the smallest side of our 2 sides.
    // 2. we create a new side equal to the modulo of the biggest side by the smallest side.
    //    is this new side a multiple of the biggest one?
    //       yes -> this one is the side of the square we're looking for!
    //       no  -> we start again: the biggest side will be the current smallest side
    //              and the smallest side will be our new side

    cout << "starting... " << w << "x" << h << endl;

    int target_side;
    int smallest_side = (w > h) ? h : w;
    int previous_smallest_side = (w > h) ? w : h;

    // recursion is nice for the programmer but evil for the memory (can lead to stack overflow)
    // we'll use a while loop
    while (true){
        
        target_side = previous_smallest_side % smallest_side;

        // cout << "smallest side:          " << smallest_side << endl;
        // cout << "previous smallest side: " << previous_smallest_side << endl;
        // cout << "target side:            " << target_side << endl;

        if (previous_smallest_side % target_side == 0){
            cout << "found target side: " << target_side << "!" << endl;
            return target_side;
        }
        previous_smallest_side = smallest_side;
        smallest_side = target_side;

        if (target_side == 0){
            return -1;
        }
    }
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