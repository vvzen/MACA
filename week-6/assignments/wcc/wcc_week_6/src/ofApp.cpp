//--------------------------------------------------------------
// @brief:      Shapes from pixels
// @shortcuts:
//      i for showing the gui
//      s for saving a screenshot
// @author:     vvzen
// @date:       27/12/2017
//--------------------------------------------------------------

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // list video devices
    vector<ofVideoDevice> devices = video_grabber.listDevices();

    for (int i = 0; i < devices.size(); i++){
        if (devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }
        else {
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
    // video
    video_grabber.setDeviceID(0);
    video_grabber.setDesiredFrameRate(60);
    video_grabber.initGrabber(640, 480);
    video_pixels.allocate(640, 480, OF_PIXELS_RGBA);

    // GUI
    gui.setup();
    gui.add(GUI_spacing.set("Spacing", 10, 3, 20));
    gui.add(GUI_tile_min_size.set("Min Tile Size", 1, 1, 4));
    gui.add(GUI_tile_max_size.set("Max Tile Size", 8, 5, 16));
    gui.add(GUI_additive_mode.set("Additive", 0));
    gui.add(GUI_subtractive_mode.set("Subtractive", 0));
    gui.add(GUI_line_mode.set("Lines", 1));
    gui.add(GUI_triangle_mode.set("Triangles", 0));
    gui.add(GUI_quad_mode.set("Quads", 0));
    gui.add(GUI_circle_mode.set("Circles", 0));
    gui.add(GUI_text_mode.set("Text", 0));
    // listeners
    GUI_additive_mode.addListener(this, &ofApp::additiveModeChanged);
    GUI_subtractive_mode.addListener(this, &ofApp::subtractiveModeChanged);
    GUI_line_mode.addListener(this, &ofApp::lineModeChanged);
    GUI_triangle_mode.addListener(this, &ofApp::triangleModeChanged);
    GUI_circle_mode.addListener(this, &ofApp::circleModeChanged);
    GUI_quad_mode.addListener(this, &ofApp::quadModeChanged);
    GUI_text_mode.addListener(this, &ofApp::textModeChanged);

    // graphic
    start_position = GUI_spacing / 2;
    font.load("fonts/Andale-Mono.ttf", 24);

    // ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    video_grabber.update();

    if (video_grabber.isFrameNew()){
        video_pixels = video_grabber.getPixels();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (GUI_additive_mode){
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        ofBackground(0);
    }
    if (GUI_subtractive_mode){
        ofBackground(255);
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    }
    else {
        ofBackground(0);
    }

    // draw the tiles using camera pixels colors
    for (int x = 0; x < ofGetWidth(); x+=GUI_spacing){
        for (int y = 0; y < ofGetHeight(); y+=GUI_spacing){

            ofPoint pos = ofPoint(start_position + x, start_position + y);

            ofColor video_color = video_pixels.getColor((pos.x + pos.y * ofGetWidth()) * 3);
            // ofColor video_color = video_pixels.getColor(pos.x, pos.y); // alternative way
            int brightness = video_color.getBrightness();
            float radius = ofMap(brightness, 0, 255, GUI_tile_min_size, GUI_tile_max_size);
            
            ofSetColor(video_color);

            // rotate shape based on brightness
            ofPushMatrix();
            ofTranslate(pos.x, pos.y, 0);
            ofRotateZ(ofMap(brightness, 0, 255, 0, 180));

            // set different drawing shapes according to gui
            if (GUI_line_mode){
                float line_length = ofMap(brightness, 0, 255, radius/16, radius);
                ofDrawLine(0, 0, line_length, line_length);
            }
            else if(GUI_circle_mode){
                ofDrawCircle(0, 0, radius, radius);
            }
            else if(GUI_triangle_mode){
                ofPushMatrix();
                ofDrawTriangle(0, -radius/2, -radius/2, radius/2, radius/2, radius/2);
                ofPopMatrix();
            }
            else if(GUI_quad_mode){
                ofPushMatrix();
                ofDrawRectangle(-radius/2, -radius/2, radius, radius);
                ofPopMatrix();
            }
            else if(GUI_text_mode){
                ofPushMatrix();
                ofScale(radius/8, radius/8, 1);
                // here we got a char casted to a string since ofTrueTypeFont wants strings!
                // string current_letter = ofToString(ASCII_CHARS[ofMap(brightness, 0, 255, 0, ASCII_CHARS_SIZE)]);
                string current_letter = ofToString(ASCII_CHARS[ofMap(x, 0, ofGetWidth(), 0, ASCII_CHARS_SIZE)]);
                font.drawString(current_letter, 0, 0);
                ofPopMatrix();
            }
            ofPopMatrix();
        }
    }

    if (GUI_additive_mode || GUI_subtractive_mode){
        ofDisableBlendMode();
    }

    if (show_gui){
        gui.draw();
    }
}

//--------------------------------------------------------------
//                          LISTENERS
//--------------------------------------------------------------
void ofApp::additiveModeChanged(bool & state){
    if (state){
        GUI_subtractive_mode.set(0);
    }
}

//--------------------------------------------------------------
void ofApp::subtractiveModeChanged(bool & state){
    if (state){
        GUI_additive_mode.set(0);
    }
}

//--------------------------------------------------------------
void ofApp::lineModeChanged(bool & state){
    if (state){
        GUI_triangle_mode.set(0);
        GUI_circle_mode.set(0);
        GUI_quad_mode.set(0);
        GUI_text_mode.set(0);
    }
}

//--------------------------------------------------------------
void ofApp::triangleModeChanged(bool & state){
    if (state){
        GUI_line_mode.set(0);
        GUI_circle_mode.set(0);
        GUI_quad_mode.set(0);
        GUI_text_mode.set(0);
    }
}

//--------------------------------------------------------------
void ofApp::circleModeChanged(bool & state){
    if (state){
        GUI_line_mode.set(0);
        GUI_triangle_mode.set(0);
        GUI_quad_mode.set(0);
        GUI_text_mode.set(0);
    }
}

//--------------------------------------------------------------
void ofApp::quadModeChanged(bool & state){
    if (state){
        GUI_line_mode.set(0);
        GUI_circle_mode.set(0);
        GUI_triangle_mode.set(0);
        GUI_text_mode.set(0);
    }
}

//--------------------------------------------------------------
void ofApp::textModeChanged(bool & state){
    if (state){
        GUI_line_mode.set(0);
        GUI_circle_mode.set(0);
        GUI_triangle_mode.set(0);
        GUI_quad_mode.set(0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'i':{
            show_gui = !show_gui;
            break;
        }
        case 's': {
            ofImage grab;
            grab.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
            grab.save("screenshot_" + ofToString(ofGetFrameNum()) + ".png");
            break;
        }
    }
}