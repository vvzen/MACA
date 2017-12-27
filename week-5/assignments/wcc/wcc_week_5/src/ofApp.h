#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		
		// int num_of_x_tiles, num_of_y_tiles;
		int spacing_x, spacing_y;
		int starting_x, starting_y;

		static const int NUM_X_TILES=16;
		static const int NUM_Y_TILES=16;
		float NOISE_SEEDS[NUM_X_TILES][NUM_Y_TILES];
		ofColor COLORS[NUM_X_TILES*NUM_Y_TILES];
		float noise_increment;
		float step_size;

		int current_crazy[2];

		// timing
		float timer;
		float ease_in_time;

		bool go_crazy;
};
