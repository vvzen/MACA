#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

struct Word {
    ofVec2f pos;
    ofVec2f size;
	int frequency;
    string text;
};

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

		// typography
		vector<Word> generateTypography(ofxJSONElement jsonSource, ofTrueTypeFont & font, float verticalSize);
		vector <Word> created_words;
		void renderTypography(ofFbo fbo, vector<Word> words);

		ofFbo typography_fbo;
		
		// input json parser
		ofxJSONElement JSON_words_count_score;
		// hashmap for storing parsed key values
		std::map<std::string, int> words_count_score;


		// font
		ofTrueTypeFont font;
		ofTrueTypeFont font_demi_bold;
		float vertical_size;

		int highest_count;
		string highest_count_word;
};
