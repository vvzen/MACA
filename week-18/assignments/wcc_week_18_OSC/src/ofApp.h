#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxImGui.h"
#define RECEIVE_PORT 8338

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		// graphics
		ofVideoGrabber cam;
		ofImage img;
		ofPoint center;
		float scale;
		float bw_level;
		vector <ofPoint> raw_points;
		ofTrueTypeFont font;
		bool show_raw_points;

		// OSC
		ofxOscReceiver receiver;
		
		// gui
		void drawImGui();
		
		ofxImGui::Gui gui;
		float GUI_interpolation_1;
		float GUI_interpolation_2;
		float GUI_interpolation_3;
		float GUI_interpolation_4;
		float GUI_interpolation_5;
		float GUI_interpolation_6;
};
