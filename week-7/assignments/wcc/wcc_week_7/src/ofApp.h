#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		// animation
		float start_delay;
		float duration;
		float timer;
		bool morphed;

		// graphics
		ofTrueTypeFont font;
		string word_1, word_2;
		vector <vector <vector <ofPoint> > > getStringAsPoints3DMatrix(ofTrueTypeFont & font, string s, int numOfSamples);
		vector <ofPoint> getStringAsPoints(ofTrueTypeFont & font, string s, int numOfSamples); // original one by theo

		// GUI
		ofxDatGui* gui;
		bool show_gui;
		ofParameter <float> GUI_noise_speed;
		ofParameter <float> GUI_noise_amount;
		ofParameter <float> GUI_line_width;
		ofParameter <float> GUI_morph;
		ofParameter <int> GUI_samples_num;
		
		// events
		void onSliderEvent(ofxDatGuiSliderEvent e);
};
