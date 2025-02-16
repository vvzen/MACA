#pragma once

#include "ofMain.h"
#include "ofxCameraAnaglyph.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxCameraAnaglyph cam;
    
    //default stuff
    vector< ofBoxPrimitive > boxes;
    vector< ofColor > colors;
    
    void setupRandomBoxes();
    void drawRandomBoxes();
    
	void setupGrid();
    void drawGrid();

	vector <ofBoxPrimitive> nodes;
	vector <ofColor> node_colors;

	vector <ofVec3f> startLine;
	vector <ofVec3f> endLine;

};
