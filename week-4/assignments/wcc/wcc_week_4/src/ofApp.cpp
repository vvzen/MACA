//--------------------------------------------------------------
// @brief:      Mandala Shapes
// @shortcuts:
//    i for toggling the GUI
//    spacebar to change shape color
// @author:     vvzen
// @date:       26/12/2017
//--------------------------------------------------------------

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    shape_color = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
    global_rot_angle = 0;

    // fill the mandala vector with infos on the shapes positions and scales
    mandala_data.push_back(ofVec3f(ofGetWidth() * 1/4, ofGetHeight() * 1/4, 1));
    mandala_data.push_back(ofVec3f(ofGetWidth() * 3/4, ofGetHeight() * 1/4, 1));
    mandala_data.push_back(ofVec3f(ofGetWidth() * 3/4, ofGetHeight() * 3/4, 1));
    mandala_data.push_back(ofVec3f(ofGetWidth() * 1/4, ofGetHeight() * 3/4, 1));
    
    // GUI
    show_gui = true;
    gui.setup("panel");
    gui.add(GUI_num_points.set("Num Points", 10, 3, 40));
    gui.add(GUI_num_steps.set("Num Steps", 10, 3, 40));
    gui.add(GUI_inner_radius.set("Inner Radius", 100, 10, 200));
    gui.add(GUI_outer_radius.set("Outer Radius", 150, 15, 400));
    gui.add(GUI_twist_speed.set("Twist speed", 0.5, 0.01, 1.5));
    gui.add(GUI_draw_outline.set("Draw Outline", 0));
    gui.add(GUI_outline_width.set("Outline Width", 2, 0.1, 4));
    gui.add(GUI_additive_mode.set("Additive Blend", 0));
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
    
    if (show_gui){
        gui.draw();
    }
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
void ofApp::keyPressed(int key){

    switch(key){
        case 'i': {
            show_gui = !show_gui;
            break;
        }
        case ' ': {
            shape_color = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
            break;
        }
    }
}