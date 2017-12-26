#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		bool is_drawing;
		float angle;
		float angle_speed;
		float shape_scale;
		float shape_increment;
		int bg_color;
		ofColor drawing_color;

		int current_mode;

		ofFbo drawing_fbo;
};
