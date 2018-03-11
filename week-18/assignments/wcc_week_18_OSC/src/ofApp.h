#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
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
		vector <ofPoint> raw_points;
		ofTrueTypeFont font;
		bool show_raw_points;
		// OSC
		ofxOscReceiver receiver;
};
