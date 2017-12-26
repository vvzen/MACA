#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);

		void drawDonut(float x, float y, float innerRadius, float outerRadius);

		ofImage reference_image;
		ofFbo reference_fbo;
		ofFbo drawing_fbo;
		ofFbo circles_fbo;
		ofFbo bg_fbo;
		ofFbo xshapes_fbo;
		ofMesh circle_mesh;

		ofImage grab;

		bool show_reference;
		bool show_drawing;
		bool show_circles;
		bool show_background;
		bool show_xshapes;
};
