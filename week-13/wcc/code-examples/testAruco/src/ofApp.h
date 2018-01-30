#pragma once

#include "ofMain.h"
#include "ofxAruco.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		
		ofVideoGrabber grabber;

		ofBaseVideoDraws * video;

		ofxAruco aruco;
		bool showMarkers;
		ofImage board;
		ofImage marker;
};
