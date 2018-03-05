#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 6448
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();

		ofxOscReceiver receiver;
        int mouseX, mouseY;

        float phone_heading;
        float phone_lat, phone_lon;
        float phone_gyro[3];

		string mouseButtonState;
        deque<string> messageBuffer;
        int maxBufferSize=20;
        int myNum;
        float myNum2;
        string myString;
        float myTime;
};
