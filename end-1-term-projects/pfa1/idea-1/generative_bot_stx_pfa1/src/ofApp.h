#pragma once

#include "ofMain.h"
#include "FlowField.hpp"
#include "Boid.hpp"
#include "FearArea.hpp"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
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
    
        void exit();

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

        void update_GUI_with_JSON_args(ofxJSONElement jsonFile);
        void saveFBOImage(string path);

        // command line arguments
        vector<string> arguments;
        string argumentsAsString;
        
        // GRAPHICS
        bool bw_mode; // black & white mode
        bool dark_mode;
        float bg_color;
        float starting_hue;

        // TYPE
		vector <Word> created_words;
		ofFbo typography_fbo;
        ofPixels type_fbo_pixels;
        string current_font;
		
		// input json parser
		ofxJSONElement JSON_words_count_score;
		// hashmap for storing parsed key values
		map<string, int> words_count_score;

		// font
		ofTrueTypeFont font;
		ofTrueTypeFont font_demi_bold;
		float vertical_size;

        // GUI
        bool show_gui;
        ofxPanel gui;
        ofParameter<float> noiseXSpeedGUI;
        ofParameter<float> noiseYSpeedGUI;
        ofParameter<float> cellSizeGUI;
        ofParameter<float> alignmentAmountGUI, separationAmountGUI;
        ofParameter<float> separationThresholdDistanceGUI;
        ofParameter<float> maxForceGUI, maxSteerGUI, maxSpeedGUI;
        ofParameter<float> fieldAttractionGUI;
        ofParameter<bool> shouldRenderGridGUI;
        ofParameter<bool> shouldRenderFearAreasGUI;
        ofParameter<bool> shouldClearCanvasGUI;
        ofParameter<bool> shouldShowFearTextGUI;
    
        // Listeners
        void changedFieldParams(float & value);
        void changedBoolParam(bool & value);
        
        // Flow field
        FlowField flowField;
    
        // Boids
        vector<Boid *> boids;
        int BOIDS_NUM;
        ofFbo boids_fbo;
    
        // Boids areas of fear
        vector <FearArea *> fearAreas;
        int FEAR_AREAS_NUM;
    
        // XML
        // Used for drawing settings
        ofxXmlSettings xmlSettings;
        // Used to store cmd line args
        ofxXmlSettings argsXml;
    
        // JSON
        ofxJSONElement jsonArguments;
        ofxJSONElement jsonFearWords;
    
        // Time
        float startTime;
        float elapsedTime;
        float APP_RUNTIME_MS;
    
        // Debug
        const bool DEBUG_JSON = false;
        const bool DEBUG_BOIDS = false;
        const bool SHOW_FEAR_AREAS = false;
        const bool USE_FEAR_AREAS = false;
        float timeLived = 0.0f;
    
        bool mouseIsPressed = false;
};
