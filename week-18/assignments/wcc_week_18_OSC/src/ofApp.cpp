#include "ofApp.h"

/*---------------------------------------------------------------
    @brief:      OSC example app
    @shortcuts:  p to show the raw data points
    @author:     vvzen
    @date:       11/03/2018
----------------------------------------------------------------*/

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(40, 100, 40);
    font.load("andale_mono.ttf", 12);
    img.allocate(640, 480, OF_IMAGE_COLOR);
    show_raw_points = false;
    // video grabber
    cam.initGrabber(640, 480);
	// OSC
    receiver.setup(RECEIVE_PORT);

    // GUI
    // these parameters control how the digital makeup is drawn
    GUI_interpolation_1 = 0.911;
    GUI_interpolation_2 = 0.337;
    GUI_interpolation_3 = 0.805;
    GUI_interpolation_4 = 0.211;
    GUI_interpolation_5 = 0.495;
    GUI_interpolation_6 = 0.947;
}

//--------------------------------------------------------------
void ofApp::update(){

    cam.update();
    if (cam.isFrameNew()){
        img.setFromPixels(cam.getPixels());
        img.mirror(false, true);
    }

    // check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);

		// global face orientation
		if(m.getAddress() == "/pose/position"){
			center.x = m.getArgAsFloat(0);
			center.y = m.getArgAsFloat(1);
			//cout << "/pose/position: " << center.x << ", " << center.y << endl;
		}
        else if(m.getAddress() == "/pose/scale"){
			scale = m.getArgAsFloat(0);
            //cout << "/pose/scale: " << scale << endl;
		}
        else if(m.getAddress() == "/gesture/eyebrow/left"){
			bw_level = ofMap(m.getArgAsFloat(0), 6, 8, 0, 255, true);
		}
        // raw points
        else if(m.getAddress() == "/raw"){
            raw_points.clear();
			for (int i = 0; i < 66; i+=2){
                float x = m.getArgAsFloat(i);
                float y = m.getArgAsFloat(i+1);
                raw_points.push_back(ofPoint(x, y));
            }
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(40);
    ofSetColor(bw_level);
    img.draw(0, 0);

    // draw all the raw positions with their index when p is pressed
    if (show_raw_points){
        ofPushStyle();
        for (int i = 0; i < raw_points.size(); i++){
            
            ofPoint current_point = raw_points.at(i);
            ofSetColor(255);
            font.drawString(ofToString(i), current_point.x, current_point.y);
        }
        ofPopStyle();
    }

    if (raw_points.size() > 0){
        
        ofPushMatrix();
        ofPushStyle();

        // raw points
        ofPoint center_nose = raw_points.at(30);
        ofPoint left_ear = raw_points.at(1);
        ofPoint left_jaw = raw_points.at(3);
        ofPoint left_chin = raw_points.at(6);
        ofPoint right_ear = raw_points.at(15);
        ofPoint right_jaw = raw_points.at(13);
        ofPoint right_chin = raw_points.at(10);

        // interpolated points
        // left
        ofPoint mid_cheek_l1 = center_nose.getInterpolated(left_ear, GUI_interpolation_1);
        ofPoint mid_cheek_l2 = center_nose.getInterpolated(left_ear, GUI_interpolation_2);
        ofPoint mid_cheek_l3 = center_nose.getInterpolated(left_jaw, GUI_interpolation_3);
        ofPoint mid_cheek_l4 = center_nose.getInterpolated(left_ear, GUI_interpolation_4);
        ofPoint mid_cheek_l5 = left_chin.getInterpolated(left_ear, GUI_interpolation_5);
        ofPoint mid_cheek_l6 = left_chin.getInterpolated(left_ear, GUI_interpolation_6);
        // right
        ofPoint mid_cheek_r1 = center_nose.getInterpolated(right_ear, GUI_interpolation_1);
        ofPoint mid_cheek_r2 = center_nose.getInterpolated(right_ear, GUI_interpolation_2);
        ofPoint mid_cheek_r3 = center_nose.getInterpolated(right_jaw, GUI_interpolation_3);
        ofPoint mid_cheek_r4 = center_nose.getInterpolated(right_ear, GUI_interpolation_4);
        ofPoint mid_cheek_r5 = right_chin.getInterpolated(right_ear, GUI_interpolation_5);
        ofPoint mid_cheek_r6 = right_chin.getInterpolated(right_ear, GUI_interpolation_6);

        // draw left shapes
        ofPath outerShape_l;
        outerShape_l.moveTo(mid_cheek_l4);
        outerShape_l.lineTo(mid_cheek_l5);
        outerShape_l.lineTo(mid_cheek_l6);
        outerShape_l.lineTo(mid_cheek_l1);
        outerShape_l.lineTo(mid_cheek_l2);
        outerShape_l.close();
        outerShape_l.setFillColor(ofColor(0));
        outerShape_l.setFilled(true);
        outerShape_l.draw();
        
        ofPath inner_triangle_l;
        inner_triangle_l.moveTo(mid_cheek_l1);
        inner_triangle_l.lineTo(mid_cheek_l2);
        inner_triangle_l.lineTo(mid_cheek_l3);
        inner_triangle_l.close();
        inner_triangle_l.setFillColor(ofColor(255));
        inner_triangle_l.setFilled(true);
        inner_triangle_l.draw();
        
        // draw right shapes
        ofPath outerShape_r;
        outerShape_r.moveTo(mid_cheek_r4);
        outerShape_r.lineTo(mid_cheek_r5);
        outerShape_r.lineTo(mid_cheek_r6);
        outerShape_r.lineTo(mid_cheek_r1);
        outerShape_r.lineTo(mid_cheek_r2);
        outerShape_r.close();
        outerShape_r.setFillColor(ofColor(255));
        outerShape_r.setFilled(true);
        outerShape_r.draw();
        
        ofPath inner_triangle_r;
        inner_triangle_r.moveTo(mid_cheek_r1);
        inner_triangle_r.lineTo(mid_cheek_r2);
        inner_triangle_r.lineTo(mid_cheek_r3);
        inner_triangle_r.close();
        inner_triangle_r.setFillColor(ofColor(0));
        inner_triangle_r.setFilled(true);
        inner_triangle_r.draw();

        ofPopStyle();
        ofPopMatrix();
    }

    drawImGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case 'p':{
            show_raw_points = !show_raw_points;
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::drawImGui(){

    gui.begin();
 	
    auto main_settings = ofxImGui::Settings();
    main_settings.windowPos = ofVec2f(10, 500); // set position
    main_settings.windowSize = ofVec2f(0.0f, 0.0f); // auto resize based on parameters dimensions
 
    ofxImGui::BeginWindow("GUI", main_settings, false);
  
    ImGui::SliderFloat("Interpolation 1", &GUI_interpolation_1, 0.0f, 1.0f);
    ImGui::SliderFloat("Interpolation 2", &GUI_interpolation_2, 0.0f, 1.0f);
    ImGui::SliderFloat("Interpolation 3", &GUI_interpolation_3, 0.0f, 1.0f);
    ImGui::SliderFloat("Interpolation 4", &GUI_interpolation_4, 0.0f, 1.0f);
    ImGui::SliderFloat("Interpolation 5", &GUI_interpolation_5, 0.0f, 1.0f);
    ImGui::SliderFloat("Interpolation 6", &GUI_interpolation_6, 0.0f, 1.0f);
  
    ofxImGui::EndWindow(main_settings);
    gui.end();
}