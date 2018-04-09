#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "vv_extrudeFont.h"

struct word {
	ofPoint pos;
	ofVec2f size;
	string text;
};

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
		string available_words[5];

		vector <word> all_words;

		// 3d stuff
		ofEasyCam cam;
		// ofCamera cam;
		ofLight key_light_1, key_light_2;
		ofMaterial text_mat;

		// string current_word;
		float current_offset;
		float extrusion_depth;

		// 2d bounding box of the current word
		ofRectangle word_bb;
		// this will hold the front, back and extruded sides meshes
		vector <ofVboMesh> word_meshes, front_meshes;
		vector <ofPath> back_paths;

		vector <vector<ofVboMesh>> all_meshes;
};
