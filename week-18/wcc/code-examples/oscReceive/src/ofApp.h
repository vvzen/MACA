#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();

		ofxOscReceiver receiver;
        int mouseX, mouseY;
		string mouseButtonState;
        deque<string> messageBuffer;
        int maxBufferSize=20;
        int myNum;
        float myNum2;
        string myString;
        float myTime;
};
