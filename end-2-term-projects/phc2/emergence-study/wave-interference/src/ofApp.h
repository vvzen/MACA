#pragma once

#include "ofMain.h"

#define WIDTH 16
#define HEIGHT 16

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

		void generate_mesh(ofVboMesh &mesh);
		void generate_mesh_2(ofVboMesh &mesh);
		ofVec3f getNormalFromTriangleVertices(vector<ofVec3f> triangleVertices);

		ofVboMesh mesh;
		ofEasyCam cam;
		
		ofLight light;

		vector <ofPoint> random_points;
};
