#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // GRAPHICS

    current_size = 4;
    next_trigger = 0;
    playhead = 0;

    min_size = 2;
    max_size = 32;

    // AUDIO

    sample_rate = 48000;
    buffer_size	= 512;

    ofxMaxiSettings::setup(sample_rate, 2, buffer_size);
    // this has to happen at the end of setup - it switches on the DAC
    ofSoundStreamSetup(2, 2, this, sample_rate, buffer_size, 4);

    ofSetCircleResolution(30);
    ofBackground(255);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update(){


    if (ofGetElapsedTimeMillis() > next_trigger){

        next_trigger += 1300;

        current_pos.x = ofRandom(ofGetWidth() / 8, ofGetWidth() * 7 / 8);
        current_pos.y = ofRandom(ofGetHeight() / 8, ofGetHeight() * 7 / 8);
        
        if (kick_track[playhead % 16] == 1){
            // cout << "tum" << endl;
            current_size = ofRandom(max_size, max_size*2);
            current_color = ofColor(255, 0, 0, 200);
        }
        else {
            // cout << "tish" << endl;
            current_size = ofRandom(min_size, max_size);
            current_color = ofColor(ofRandom(255), 200);
        }

        dot new_dot;
        new_dot.pos = ofPoint(current_pos.x, current_pos.y);
        new_dot.col = current_color;
        new_dot.size = current_size;
        dots.push_back(new_dot);
        playhead++;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);

    ofPushStyle();
    for (int i = 0; i < dots.size(); i++){
        ofSetColor(dots.at(i).col);
        ofDrawCircle(dots.at(i).pos.x, dots.at(i).pos.y, dots.at(i).size, dots.at(i).size);
    }
    // ofSetColor(current_color);
    // ofDrawCircle(current_pos.x, current_pos.y, current_size, current_size);
    ofPopStyle();

    // drawImGui();
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int numChannels){

    for (int i = 0; i < bufferSize; i++){
        
        float carrier_frequency = ofMap(current_size, min_size, max_size, 1000, 50);

        float freq_mod =osc2.saw(osc3.phasor(0.05, 0, 100)) * 200;
        float amp_mod = osc4.pulse(current_size * 0.1, 0.5);
    
        double wave = osc1.sawn(carrier_frequency + freq_mod) * amp_mod;

        output[i] = wave;
        output[i + 1] = wave;
    }
}

//--------------------------------------------------------------
 void ofApp::drawImGui(){
 
    gui.begin();
 	
    auto main_settings = ofxImGui::Settings();
    main_settings.windowPos = ofVec2f(10, 500); // set position
    main_settings.windowSize = ofVec2f(0.0f, 0.0f); // auto resize based on parameters dimensions
 
    ofxImGui::BeginWindow("GUI", main_settings, false);

    // AUDIO
    ImGui::Text("Audio");
    // ImGui::SliderFloat("Carrier Frequency", &GUI_carrier_frequency, 1.0f, 1200.0f);
    // ImGui::SliderFloat("Carrier Cycle", &GUI_carrier_cycle, 0.0f, 1.0f);
    // ImGui::SliderFloat("Amp Frequency 1", &GUI_amp_frequency_1, 0.1f, 200.0f);
    ImGui::SliderFloat("Frequency Mod 1", &GUI_frequency_mod_1, 0.1f, 1000.0f);
    ImGui::SliderFloat("Frequency Mod 2", &GUI_frequency_mod_2, 0.1f, 600.0f);
    // ImGui::SliderFloat("Timer Frequency", &GUI_timer_frequency, 0.1f, 20);
  
    ofxImGui::EndWindow(main_settings);
    gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}