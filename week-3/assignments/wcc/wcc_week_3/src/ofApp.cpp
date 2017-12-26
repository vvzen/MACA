//--------------------------------------------------------------
// @brief:     Animated Brushes
// @shortcuts:
//      Spacebar to change color
//      C to clear the background
//      R to reverse the drawing mode (blending mode add/multiply, dark/light bg)
//      1 and 2 to change drawing shape
//      UP and DOWN arrow to change shape size
//      LEFT and RIGHT arrow to change shape rotation speed
//      S to save the current image
// @author:    vvzen
// @date:      23/12/2017
//--------------------------------------------------------------

#define MODE_1 1
#define MODE_2 2

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // init drawing variables
    angle = 0;
    angle_speed = 1.4;
    shape_scale = 10;
    shape_increment = 0.5;
    drawing_color = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
    bg_color = 255;
    current_mode = MODE_1;

    // init fbo for drawing
    drawing_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 8);
    drawing_fbo.begin();
        ofClear(bg_color);
        ofBackground(bg_color);
    drawing_fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (is_drawing){
        angle += angle_speed;

        if (angle > 360){
            angle = 0;
        } 

        drawing_fbo.begin();
        ofPushStyle();
            if (bg_color > 127){
                ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
            }
            else {
                ofEnableBlendMode(OF_BLENDMODE_ADD);
            }
            ofPushMatrix();
            ofTranslate(ofGetMouseX(), ofGetMouseY());
            ofRotate(angle);
            ofScale(shape_scale, shape_scale, 0);
            ofSetColor(drawing_color);
            
            // mode 1: rect
            if (current_mode == MODE_1){
                ofNoFill();
                ofDrawRectangle(0, 0, 10, 10);
            }
            // mode 2: orthogonal lines
            if (current_mode == MODE_2){
                ofDrawLine(0, 0, 10, 10);
                ofRotateZ(90);
                ofDrawLine(0, 0, 10, 10);
            }
            
            ofPopMatrix();
        ofDisableBlendMode();
        ofPopStyle();
        drawing_fbo.end();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(bg_color);
    drawing_fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key){
        case OF_KEY_UP: {
            shape_scale += shape_increment;
            break;
        }
        case OF_KEY_DOWN: {
            shape_scale -= shape_increment;
            break;
        }
        case OF_KEY_RIGHT: {
            angle_speed += 0.1;
            break;
        }
        case OF_KEY_LEFT: {
            angle_speed -= 0.1;
            break;
        }
        case ' ': {
            drawing_color.r = ofRandom(0, 255);
            drawing_color.g = ofRandom(0, 255);
            drawing_color.b = ofRandom(0, 255);
            break;
        }
        case 'c': {
            drawing_fbo.begin();
                ofBackground(bg_color);
            drawing_fbo.end();
            break;
        }
        case 's': {
            ofImage image;
            image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
            image.save("screenshot_" + ofToString(ofGetFrameNum()) + ".png");
            break;
        }
        case 'r': {
            // reverse bg color
            bg_color = (bg_color > 127) ? 0 : 255;
            drawing_fbo.begin();
                ofBackground(bg_color);
            drawing_fbo.end();
            break;
        }
        // num 1
        case 49: {
            current_mode = MODE_1;
            break;
        }
        // num 2
        case 50: {
            current_mode = MODE_2;
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    is_drawing = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    is_drawing = false;
}
