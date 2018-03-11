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
        else if(m.getAddress() == "/pose/orientation"){
			// float x = m.getArgAsFloat(0);
			// float y = m.getArgAsFloat(1);
			// float z = m.getArgAsFloat(2);
			//cout << "/pose/orientation: " << x << ", " << y << ", " << z << endl;
		}
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
    img.draw(0, 0);

    // center red nose
    /* ofPushMatrix();
    
    ofPushStyle();
    ofTranslate(center.x, center.y);
    ofScale(scale, scale);
    ofSetColor(255, 10, 2);
    ofDrawCircle(0, 0, 6, 6);
    ofPopStyle();

    ofPopMatrix(); */
    

    // draw all the raw positions with their index
    if (show_raw_points){
        ofPushStyle();
        for (int i = 0; i < raw_points.size(); i++){
            // ofColor col;
            // col.setHsb(ofMap(i, 0, raw_points.size(), 0, 360), 120, 120, 255);
            ofPoint current_point = raw_points.at(i);
            ofSetColor(255);
            //ofDrawCircle(current_point.x, current_point.y, 4, 4);
            font.drawString(ofToString(i), current_point.x, current_point.y);
        }
        ofPopStyle();
    }

    if (raw_points.size() > 0){
        
        ofPushMatrix();
        ofPushStyle();

        ofPoint center_nose = raw_points.at(30);
        ofPoint left_ear = raw_points.at(1);
        ofPoint right_ear = raw_points.at(15);
        ofPoint left_jaw = raw_points.at(3);
        ofPoint right_jaw = raw_points.at(13);
        ofPoint left_chin = raw_points.at(6);
        ofPoint right_chin = raw_points.at(10);

        //ofTranslate(center_nose.x, center_nose.y);
        ofSetColor(255);
        
        ofDrawCircle(center_nose.x, center_nose.y, 6, 6);
        ofDrawCircle(left_ear.x, left_ear.y, 6, 6);
        ofDrawCircle(right_ear.x, right_ear.y, 6, 6);
        
        // left
        ofPoint mid_cheek_l1 = center_nose.getInterpolated(left_ear, 0.85);
        ofPoint mid_cheek_l2 = center_nose.getInterpolated(left_ear, 0.40);
        ofPoint mid_cheek_l3 = center_nose.getInterpolated(left_jaw, 0.70);
        ofPoint mid_cheek_l4 = center_nose.getInterpolated(left_ear, 0.25);
        ofPoint mid_cheek_l5 = left_chin.getInterpolated(left_ear, 0.35);
        ofPoint mid_cheek_l6 = left_chin.getInterpolated(left_ear, 0.85);
        // right
        ofPoint mid_cheek_r1 = center_nose.getInterpolated(right_ear, 0.85);
        ofPoint mid_cheek_r2 = center_nose.getInterpolated(right_ear, 0.40);
        ofPoint mid_cheek_r3 = center_nose.getInterpolated(right_jaw, 0.70);
        ofPoint mid_cheek_r4 = center_nose.getInterpolated(right_ear, 0.25);
        ofPoint mid_cheek_r5 = right_chin.getInterpolated(right_ear, 0.35);
        ofPoint mid_cheek_r6 = right_chin.getInterpolated(right_ear, 0.85);

        // left shape

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
        
        // right shapes

        ofPath outerShape_r;
        outerShape_r.moveTo(mid_cheek_r4);
        outerShape_r.lineTo(mid_cheek_r5);
        outerShape_r.lineTo(mid_cheek_r6);
        outerShape_r.lineTo(mid_cheek_r1);
        outerShape_r.lineTo(mid_cheek_r2);
        outerShape_r.close();
        outerShape_r.setFillColor(ofColor(0));
        outerShape_r.setFilled(true);
        outerShape_r.draw();
        
        ofPath inner_triangle_r;
        inner_triangle_r.moveTo(mid_cheek_r1);
        inner_triangle_r.lineTo(mid_cheek_r2);
        inner_triangle_r.lineTo(mid_cheek_r3);
        inner_triangle_r.close();
        inner_triangle_r.setFillColor(ofColor(255));
        inner_triangle_r.setFilled(true);
        inner_triangle_r.draw();

        ofPopStyle();
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case 'p':{
            cout << "here" << endl;
            show_raw_points = !show_raw_points;
            break;
        }
    }
}