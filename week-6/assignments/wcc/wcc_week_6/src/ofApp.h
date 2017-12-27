#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		
		// video
		ofVideoGrabber video_grabber;
		ofPixels video_pixels;
		int start_position;

		ofTrueTypeFont font;
		// const static int ASCII_CHARS_SIZE = 71;
		// const string ASCII_CHARS = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
		const static int ASCII_CHARS_SIZE = 26;
		const string ASCII_CHARS = "abcdefghijklmnopqrstuvwxyz";

		// GUI
		bool show_gui;
		ofxPanel gui;
		ofParameter<float> GUI_spacing;
		ofParameter<float> GUI_tile_max_size;
		ofParameter<float> GUI_tile_min_size;
		ofParameter<bool> GUI_additive_mode;
		ofParameter<bool> GUI_subtractive_mode;

		ofParameter<bool> GUI_line_mode;
		ofParameter<bool> GUI_triangle_mode;
		ofParameter<bool> GUI_quad_mode;
		ofParameter<bool> GUI_circle_mode;
		ofParameter<bool> GUI_text_mode;

		// listeners
		void additiveModeChanged(bool & state);
		void subtractiveModeChanged(bool & state);
		void lineModeChanged(bool & state);
		void triangleModeChanged(bool & state);
		void circleModeChanged(bool & state);
		void quadModeChanged(bool & state);
		void textModeChanged(bool & state);
};
