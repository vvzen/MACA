#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void branch(float len);
		void mousePressed(int x, int y, int button);

		float theta;
};
