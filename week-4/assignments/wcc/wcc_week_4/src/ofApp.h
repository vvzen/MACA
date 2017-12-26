#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		
		void drawStar(float x, float y, float inner_radius, float outer_radius, int npoints, bool draw_outline);

		void drawMandala(float x, float y, float rot_offset, float scale);
		void drawMandala2(float x, float y, float radius, int num_circles);
		void drawMandala3(float x, float y, float outer_radius, float mid_radius, int nshapes);

		ofColor shape_color;
		float global_rot_angle, global_angle_step;
		vector <ofVec3f> mandala_data;

		// GUI
		bool show_gui;
		ofParameter<float> GUI_inner_radius;
		ofParameter<float> GUI_outer_radius;
		ofParameter<float> GUI_twist_speed;
		ofParameter<int> GUI_num_points;
		ofParameter<int> GUI_num_steps;
		ofParameter<bool> GUI_draw_outline;
		ofParameter<float> GUI_outline_width;
		ofParameter<bool> GUI_additive_mode;
		ofxPanel gui;
};
