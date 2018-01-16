#pragma once
#include "ofMain.h"
#include "BallSystem.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void mousePressed(int x, int y, int button);
		void keyPressed(int key);
		BallSystem ballSys;
};
