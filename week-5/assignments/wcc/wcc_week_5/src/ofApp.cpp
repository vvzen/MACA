#include "ofApp.h"

//--------------------------------------------------------------
// @brief:      Harlem Shake
// @shortcuts:
//      first  left mouse click to make it the crazyness happen!
//      second left mouse click to make it the crazyness disappear..
//      r to change current crazy one
//      s to save current frame
// @author:     vvzen
// @date:       27/12/2017
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::setup(){
    
    spacing_x = ofGetWidth() / NUM_X_TILES;
    spacing_y = ofGetHeight() / NUM_Y_TILES;
    starting_x = 0 + spacing_x / 2;
    starting_y = 0 + spacing_y / 2;
    step_size = 20;
    noise_increment = 0.035f;

    go_crazy = false;
    current_crazy[0] = ofRandom(NUM_X_TILES);
    current_crazy[1] = ofRandom(NUM_Y_TILES);
    cout << "current_crazy[0]: " << current_crazy[0] << endl;
    cout << "current_crazy[1]: " << current_crazy[1] << endl << endl;

    timer = 0.0f;
    ease_in_time = 20.0f;

    // init random values for each cell
    for (int i = 0; i < NUM_X_TILES; i++){
        for (int j = 0; j < NUM_Y_TILES; j++){
            NOISE_SEEDS[i][j] = ofRandom(0, 1000);
            // color is a 1d array used to store colors for all the tiles
            COLORS[i + j * NUM_X_TILES] = ofColor::fromHsb(ofRandom(130, 255), ofRandom(200, 255), 90);
        }
    }

    ofEnableAlphaBlending();
    ofSetBackgroundAuto(false);
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(0, 0, 0, 50);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    for (int i = 0; i < NUM_X_TILES; i++){
        for (int j = 0; j < NUM_Y_TILES; j++){
            
            float loc_x = starting_x + i * spacing_x;
            float loc_y = starting_y + j * spacing_y;
            
            ofSetColor(255, 255, 255, 50);

            // compute offset using noise and the particular seed of every tile
            float offset_x = ofSignedNoise(NOISE_SEEDS[i][j]) * step_size;
            float offset_y = ofSignedNoise(NOISE_SEEDS[i][j] + 500) * step_size;
            
            if (go_crazy){
                
                // rules for the special crazy one
                if (i == current_crazy[0] && j == current_crazy[1]){
                    ofSetColor(234, 225, 0, 50);
                }
                // rules for all the other crazy ones
                else {
                    ofSetColor(COLORS[i + j * NUM_X_TILES]);
                    // EASE IN
                    if (timer < ease_in_time){
                        float ease_in_multiplier = ofMap(timer, 0, ease_in_time, 0.01, 1);
                        
                        offset_x *= ease_in_multiplier;
                        offset_y *= ease_in_multiplier;

                        timer += 0.001f;
                    }
                }

                loc_x += offset_x;
                loc_y += offset_y;

                NOISE_SEEDS[i][j] += noise_increment;
            }
            else {
                // rules for the special crazy one
                if (i == current_crazy[0] && j == current_crazy[1]){

                    loc_x += offset_x;
                    loc_y += offset_y;

                    NOISE_SEEDS[i][j] += noise_increment;
                    ofSetColor(234, 225, 0, 50);
                }
                // rules for all the other crazy ones
                else {
                    // EASE OUT
                    if (timer > 0){
                        ofSetColor(COLORS[i + j * NUM_X_TILES]);
                        float ease_out_multiplier = ofMap(timer, 0, ease_in_time, 0.01, 1);
                        offset_x *= ease_out_multiplier;
                        offset_y *= ease_out_multiplier;

                        loc_x += offset_x;
                        loc_y += offset_y;

                        NOISE_SEEDS[i][j] += noise_increment;

                        timer -= 0.001f;
                    }
                }
            }

            ofDrawCircle(loc_x, loc_y, 3, 3);
            ofDrawRectangle(loc_x - 3, loc_y + 1.5, 5, 5);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case 'r': {
            current_crazy[0] = ofRandom(NUM_X_TILES);
            current_crazy[1] = ofRandom(NUM_Y_TILES);
            cout << "current_crazy[0]: " << current_crazy[0] << endl;
            cout << "current_crazy[1]: " << current_crazy[1] << endl << endl;
            break;
        }
        case 's': {
            ofImage grab;
            grab.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
            grab.save("screenshot_" + ofToString(ofGetFrameNum()) + ".png");
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    go_crazy = !go_crazy;
}