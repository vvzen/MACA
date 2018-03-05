#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxImGui.h"

struct dot {
    ofPoint pos;
    float size;
    ofColor col;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);

		// GRAPHICS
		vector<dot> dots;
		ofPoint current_pos;
		float current_size;
		ofColor current_color;
		int next_trigger;

		float min_size, max_size;

		// AUDIO
		void audioOut(float * output, int bufferSize, int numChannels);
		
		int buffer_size;
        int sample_rate;
		int playhead;
		int kick_track[16] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0};
		
		maxiOsc osc1, osc2, osc3, osc4;
		maxiOsc metronome;

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
};
