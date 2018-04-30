#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "globals.h"
#include "DifferentialLine.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void save_mesh();

		void drawImGui();
		
		DifferentialLine differential_line;
		ofEasyCam cam;

		void create_circle_with_nodes();

		ofxImGui::Gui gui;
};
