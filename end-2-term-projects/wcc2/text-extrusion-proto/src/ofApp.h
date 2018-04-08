#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "vv_extrudeFont.h"

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

		ofTrueTypeFont font;

		ofEasyCam cam;
		ofLight key_light;
		ofMaterial text_mat;

		string current_word;
		float current_offset;
		int extrusion_depth;

		// 2d bounding box of the current word
		ofRectangle word_bb;
		// this will hold the front, back and extruded sides meshes
		vector <ofVboMesh> word_meshes, front_meshes;
		vector <ofPath> back_paths;
};
