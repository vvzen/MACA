#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"


//For OSC:
#define HOST "localhost"
#define PORT 6448

class ofApp : public ofBaseApp{

	public:
		void setup();
        void exit();

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
    
    //For GUI;
    void colorButtonPressed();
    void xSliderChanged(float & newX);
    void ySliderChanged(float & newY);
    bool bHide;
    
    ofxFloatSlider x;
    ofxFloatSlider y;
    ofxButton colorButton;
    
    ofxPanel gui;
    
    //For OSC:
    ofxOscSender sender;
		
};
