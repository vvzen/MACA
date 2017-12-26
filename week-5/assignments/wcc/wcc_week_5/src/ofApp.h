#pragma once

#include "ofMain.h"

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		// int num_of_x_tiles, num_of_y_tiles;
		int spacing_x, spacing_y;
		int starting_x, starting_y;

		static const int NUM_X_TILES=32;
		static const int NUM_Y_TILES=32;
		float NOISE_SEEDS[NUM_X_TILES][NUM_Y_TILES];
		float noise_increment;

		bool go_crazy;
		float step_size = 0.01;
};
