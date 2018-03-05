#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // GRAPHICS
    shape_color = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
    global_rot_angle = 0;

    // fill the mandala vector with infos on the shapes positions and scales
    mandala_data.push_back(ofVec3f(ofGetWidth() * 1/4, ofGetHeight() * 1/4, 1));
    mandala_data.push_back(ofVec3f(ofGetWidth() * 3/4, ofGetHeight() * 1/4, 1));
    mandala_data.push_back(ofVec3f(ofGetWidth() * 3/4, ofGetHeight() * 3/4, 1));
    mandala_data.push_back(ofVec3f(ofGetWidth() * 1/4, ofGetHeight() * 3/4, 1));

    // AUDIO

    sample_rate = 48000;
    buffer_size	= 512;

    ofxMaxiSettings::setup(sample_rate, 2, buffer_size);
    // this has to happen at the end of setup - it switches on the DAC
    ofSoundStreamSetup(2, 2, this, sample_rate, buffer_size, 4);

}

//--------------------------------------------------------------
void ofApp::update(){
    // rotate everything!
    global_rot_angle += GUI_twist_speed;
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushStyle();
    ofFill();
    if (GUI_additive_mode){
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofBackground(10);
    }
    else {
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        ofBackground(255);
    }

    // draw the 4 outer mandalas
    for (int i = 0; i < mandala_data.size(); i++){
        drawMandala(mandala_data[i].x, mandala_data[i].y, float(i), mandala_data[i].z);
    }

    // draw the center mandala
    drawMandala3(ofGetWidth()/2, ofGetHeight()/2, GUI_outer_radius, GUI_inner_radius, GUI_num_points);

    ofDisableBlendMode();
    ofPopStyle();

    drawImGui();
}


//--------------------------------------------------------------
void ofApp::drawMandala(float x, float y, float rot_offset, float scale){
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(x, y, 0);
    ofScale(scale, scale, 1); // master scale of the whole shape

    // create the actual mandala with repetitions of the star shape
    for (int i = 1; i < GUI_num_steps+1; i++){
        
        // change color based on shape iteration
        ofColor current_color;
        if (GUI_additive_mode){
            current_color.r = ofMap(i, 0, GUI_num_steps-1, 0, shape_color.r);
            current_color.g = ofMap(i, 0, GUI_num_steps-1, 0, shape_color.g);
            current_color.b = ofMap(i, 0, GUI_num_steps-1, 0, shape_color.b);
            current_color.a = 30;
        }
        else {
            current_color.r = ofMap(i, 0, GUI_num_steps-1, 255, shape_color.r);
            current_color.g = ofMap(i, 0, GUI_num_steps-1, 255, shape_color.g);
            current_color.b = ofMap(i, 0, GUI_num_steps-1, 255, shape_color.b);
        }

        ofSetColor(current_color);
        ofPushMatrix();

        ofRotateZ(i * global_rot_angle + rot_offset * 5);
        
        float scale_factor = ofMap(i, 0, GUI_num_steps-1, 1, 0.1);
        ofScale(scale_factor, scale_factor, 1);
        
        drawStar(0, 0, GUI_inner_radius, GUI_outer_radius, GUI_num_points, GUI_draw_outline);
        ofPopMatrix();
    }
    
    ofPopStyle();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawMandala2(float x, float y, float radius, int num_circles){

    ofPushStyle();
    ofSetCircleResolution(60);

    float angle_increment = 360.0 / num_circles;

    for (int angle = 0; angle < 360.0; angle+=angle_increment){

        ofSetColor(shape_color);

        ofPoint v1 = ofPoint(cos(ofDegToRad(angle)) * radius, sin(ofDegToRad(angle)) * radius);

        ofPushMatrix();

        ofTranslate(x, y, 0);
        ofRotateZ(global_rot_angle);
        ofDrawCircle(v1.x, v1.y, GUI_inner_radius, GUI_inner_radius);

        ofPopMatrix();
    }

    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawMandala3(float x, float y, float outer_radius, float mid_radius, int nshapes){
    
    float angle_increment = 360.0f / nshapes;
    float offset = 360.0f / 20.0f;

    ofPushStyle();
    ofPushMatrix();
    ofTranslate(x, y, 0);

    // create the actual mandala with repetitions of the base shape
    for (int i = 1; i < GUI_num_steps+1; i++){
        
        // change color based on shape iteration
        ofColor current_color;
        if (GUI_additive_mode){
            current_color.r = ofMap(i, 0, GUI_num_steps-1, 0, shape_color.r);
            current_color.g = ofMap(i, 0, GUI_num_steps-1, 0, shape_color.g);
            current_color.b = ofMap(i, 0, GUI_num_steps-1, 0, shape_color.b);
            current_color.a = 30;
        }
        else {
            current_color.r = ofMap(i, 0, GUI_num_steps-1, 255, shape_color.r);
            current_color.g = ofMap(i, 0, GUI_num_steps-1, 255, shape_color.g);
            current_color.b = ofMap(i, 0, GUI_num_steps-1, 255, shape_color.b);
        }

        ofSetColor(current_color);
        ofPushMatrix();
        
        ofRotateZ(i * global_rot_angle + i * 10);

        float scale_factor = ofMap(i, 1, GUI_num_steps+1, 1, 0.1);
        ofScale(scale_factor, scale_factor, 1);
        
        // base shape, could be wrapped in another function but this approach is more manageable atm
        for (int angle = 1; angle < 360.0f; angle += angle_increment){
            
            ofSetLineWidth(GUI_outline_width);
            ofSetPolyMode(OF_POLY_WINDING_NONZERO);
            //ofTranslate(x, y);
            ofBeginShape();
            ofPoint v1(0, 0);
            ofVertex(v1);
            ofPoint v2(cos(ofDegToRad(angle - offset)) * mid_radius, sin(ofDegToRad(angle - offset)) * mid_radius);
            // ofDrawCircle(v2.x, v2.y, 2, 2);
            ofVertex(v2);
            ofPoint v3(cos(ofDegToRad(angle)) * outer_radius, sin(ofDegToRad(angle)) * outer_radius);
            // ofDrawCircle(v3.x, v3.y, 2, 2);
            ofVertex(v3);
            ofPoint v4(cos(ofDegToRad(angle + offset)) * mid_radius, sin(ofDegToRad(angle + offset)) * mid_radius);
            // ofDrawCircle(v4.x, v4.y, 2, 2);
            ofVertex(v4);
            ofEndShape();

            if (GUI_draw_outline){
                ofSetLineWidth(GUI_outline_width);
                ofPolyline line;
                line.curveTo(v1);
                line.curveTo(v2);
                line.curveTo(v3);
                line.curveTo(v4);
                line.curveTo(v1);
                line.draw();
            }
        }
        ofPopMatrix();
    }
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawStar(float x, float y, float inner_radius, float outer_radius, int npoints, bool draw_outline){

    float angle_increment = 360.0 / npoints;
    float half_angle = angle_increment / 4.0;

    ofPolyline line;

    // draw filled shape
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    ofBeginShape();
    for (int angle = 0; angle < 360.0; angle+=angle_increment){

        ofPushMatrix();
        ofTranslate(x, y);
        ofPoint v1 = ofPoint(cos(ofDegToRad(angle)) * outer_radius, sin(ofDegToRad(angle)) * outer_radius);
        ofPoint v2 = ofPoint(cos(ofDegToRad(angle + half_angle)) * inner_radius, sin(ofDegToRad(angle + half_angle)) * inner_radius);
        ofVertex(v1);
        ofVertex(v2);
        ofPopMatrix();

        if (draw_outline){
            line.addVertex(v1);
            line.addVertex(v2);
        }
    }
    
    // draw outline
    if(draw_outline){
        ofSetLineWidth(GUI_outline_width);
        ofPushMatrix();
        ofTranslate(x, y);
        line.draw();
        ofPopMatrix();
    }
    ofEndShape();
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int numChannels){

    for (int i = 0; i < bufferSize; i++){

        // Make the sound texture vary continuously over a period of 20-30 seconds through the use of low-frequency oscillators, so that the sound texture develops over the entire period.
        // float frequency_modulation = osc2.sinewave(osc3.phasor(0.025, 0, 100)) * GUI_frequency_mod_2;
        float frequency_modulation = osc2.sinewave(GUI_frequency_mod_1) * GUI_outer_radius;
        float amplitude_modulation = osc4.sawn(GUI_twist_speed * 4);

        double wave = osc1.pulse(GUI_carrier_frequency + frequency_modulation, GUI_carrier_cycle) * amplitude_modulation;
        // double wave = osc1.saw(GUI_carrier_frequency + frequency_modulation) * amplitude_modulation;

        // double wave = osc1.pulse(GUI_carrier_frequency + frequency_modulation, GUI_carrier_cycle) * ADSRout;

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
  
    // GRAPHICS
    ImGui::Text("Graphics");
    ImGui::SliderFloat("Inner Radius", &GUI_inner_radius, 100, 200);
    ImGui::SliderFloat("Outer Radius", &GUI_outer_radius, 150, 400);
    ImGui::SliderFloat("Twist speed", &GUI_twist_speed, 0.1, 1.5);

    ImGui::Checkbox("Draw Outline", &GUI_draw_outline);
    ImGui::SliderInt("Num Points", &GUI_num_points, 10, 40);
    ImGui::SliderInt("Num Steps", &GUI_num_steps, 10, 40);
    ImGui::SliderFloat("Outline Width", &GUI_outline_width, 2, 4);
    ImGui::Checkbox("Additive Blend", &GUI_additive_mode);

    // AUDIO
    ImGui::Text("Audio");
    ImGui::SliderFloat("Carrier Frequency", &GUI_carrier_frequency, 1.0f, 1200.0f);
    ImGui::SliderFloat("Carrier Cycle", &GUI_carrier_cycle, 0.0f, 1.0f);
    // ImGui::SliderFloat("Amp Frequency 1", &GUI_amp_frequency_1, 0.1f, 200.0f);
    ImGui::SliderFloat("Frequency Mod 1", &GUI_frequency_mod_1, 0.1f, 1000.0f);
    // ImGui::SliderFloat("Frequency Mod 2", &GUI_frequency_mod_2, 0.1f, 600.0f);
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