#pragma once

#include "ofMain.h"

struct Node {
	ofPoint pos;
	int id;
	Node * previous;
	Node * next;
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

		void offset_points();
		void offset_points_var_a();

		ofEasyCam cam;

		ofMesh mesh;

		std::list <Node> nodes;

		bool evolve;
		
};
