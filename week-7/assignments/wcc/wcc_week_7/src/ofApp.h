#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

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


		ofTrueTypeFont font;
		vector <ofTTFCharacter> font_paths;
		string current_text;
		string word_1, word_2;
		vector <vector <vector <ofPoint> > > getStringAsPoints3DMatrix(ofTrueTypeFont & font, string s, int numOfSamples);
		vector <ofPoint> getStringAsPoints(ofTrueTypeFont & font, string s, int numOfSamples);
		float timer;
		bool morphed;

		ofxDatGui* gui;
		ofParameter <float> GUI_noise_speed;
		ofParameter <float> GUI_noise_amount;
		ofParameter <float> GUI_line_width;
		ofParameter <float> GUI_morph;
		
		// events
		void onSliderEvent(ofxDatGuiSliderEvent e);
};
