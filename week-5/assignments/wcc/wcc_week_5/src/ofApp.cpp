#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    spacing_x = ofGetWidth() / NUM_X_TILES;
    spacing_y = ofGetHeight() / NUM_Y_TILES;
    starting_x = 0 + spacing_x / 2;
    starting_y = 0 + spacing_y / 2;
    step_size = 20;
    noise_increment = 0.02;
    go_crazy = false;

    // init random values for each cell
    for (int i = 0; i < NUM_X_TILES; i++){
        for (int j = 0; j < NUM_Y_TILES; j++){
            NOISE_SEEDS[i][j] = ofRandom(0, 1000);
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
    
    ofSetColor(0, 0, 0, 20);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255, 255, 255, 50);

    for (int i = 0; i < NUM_X_TILES; i++){
        for (int j = 0; j < NUM_Y_TILES; j++){
            
            float loc_x = starting_x + i * spacing_x;
            float loc_y = starting_y + j * spacing_y;
            
            if (go_crazy){

                float offset_x = ofSignedNoise(NOISE_SEEDS[i][j]) * step_size;
                float offset_y = ofSignedNoise(NOISE_SEEDS[i][j] + 500) * step_size;
                loc_x += offset_x;
                loc_y += offset_y;

                NOISE_SEEDS[i][j] += noise_increment;
            }
            else {
                if (i == 20 && j == 20){

                    float offset_x = ofSignedNoise(NOISE_SEEDS[i][j]) * step_size;
                    float offset_y = ofSignedNoise(NOISE_SEEDS[i][j] + 500) * step_size;
                    loc_x += offset_x;
                    loc_y += offset_y;

                    NOISE_SEEDS[i][j] += noise_increment;
                }
            }

            ofDrawCircle(loc_x, loc_y, 2, 2);

        }
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
    go_crazy = !go_crazy;
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
