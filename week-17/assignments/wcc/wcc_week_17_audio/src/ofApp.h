#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxImGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);

		// GRAPHICS
		void drawStar(float x, float y, float inner_radius, float outer_radius, int npoints, bool draw_outline);
		void drawMandala(float x, float y, float rot_offset, float scale);
		void drawMandala2(float x, float y, float radius, int num_circles);
		void drawMandala3(float x, float y, float outer_radius, float mid_radius, int nshapes);

		ofColor shape_color;
		float global_rot_angle, global_angle_step;
		vector <ofVec3f> mandala_data;

		// AUDIO
		void audioOut(float * output, int bufferSize, int numChannels);
		int buffer_size;
        int sample_rate;
		maxiOsc osc1, osc2, osc3, osc4;
		maxiOsc timer; // this is the metronome

		int current_count, last_count;

		// GUI
		void drawImGui();
		ofxImGui::Gui gui;

		float GUI_carrier_frequency;
		float GUI_carrier_cycle;
		float GUI_amp_frequency_1;
		float GUI_timer_frequency;
		float GUI_frequency_mod_1;
		float GUI_frequency_mod_2;

		// GUI
		bool show_gui;
		float GUI_inner_radius;
		float GUI_outer_radius;
		float GUI_twist_speed;
		float GUI_outline_width;
		int GUI_num_points;
		int GUI_num_steps;
		bool GUI_draw_outline;
		bool GUI_additive_mode;
};
