#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"

//For OSC:
#define HOST1 "localhost"
#define HOST2 "localhost"
#define PORT1 6448
#define PORT2 6449

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    void updateTempo();


    long lastTime;
    long waitMillis = 1000;
    void sendOsc(int beat);
    int thisBeat = 0;
    int beatDiv = 4;
    int bpm_int = 0;

    ofxOscSender sender1;
    ofxOscSender sender2;
};
