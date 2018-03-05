#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "10.100.63.52"
#define PORT 12345
#define RECEIVE_PORT 99999

//--------------------------------------------------------
class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		void mouseDragged(int x, int y, int button);

		ofxOscSender sender;
		vector<ofPoint> positions;


		ofxOscReceiver receiver;
		vector<ofPoint> received_points;

		vector<ofPolyline> received_lines;
};
