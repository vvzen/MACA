#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

#define MESH_WIDTH 128
#define MESH_HEIGHT 128

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);

		void generate_random_points(int num);
		void generate_mesh(int num_cols, int num_rows, float frequency, float amp_factor);
		void drawImGui();

		of3dPrimitive waves_primitive;

		ofEasyCam cam;
		
		ofLight light;

		vector <ofPoint> random_points;
		int num_random_points;

		// GUI
		ofxImGui::Gui gui;
		int GUI_resolution_x, GUI_resolution_y;
		int GUI_num_random_points;
		float GUI_frequency, GUI_amp_factor;
};
