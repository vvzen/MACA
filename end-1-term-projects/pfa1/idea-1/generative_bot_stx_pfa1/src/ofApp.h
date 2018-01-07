#pragma once // include this file only once

#include "globals.h"
#include "ofMain.h"
#include "boid.hpp"
#include "flowField.hpp"
#include "fearArea.hpp"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "ofxJSON.h"
#include "type.h"

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
        void save_fbo_image(string path);

        // command line arguments
        vector<string> arguments;
        
        // GRAPHICS
        bool bw_mode; // black & white mode
        bool dark_mode;
        float bg_color;
        float starting_hue;
        bool save_animation;

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
        ofParameter<float> noise_x_speed_GUI;
        ofParameter<float> noise_y_speed_GUI;
        ofParameter<float> cell_size_GUI;
        ofParameter<float> alignment_amount_GUI, separation_amount_GUI;
        ofParameter<float> separation_threshold_distance_GUI;
        ofParameter<float> max_force_GUI, max_steer_GUI, max_speed_GUI;
        ofParameter<float> field_attraction_GUI;
        ofParameter<bool> render_grid_GUI;
        ofParameter<bool> clear_canvas_GUI;
        ofParameter<bool> show_fear_text_GUI;
    
        // Listeners
        void changed_field_param(float & value);
        void changed_bool_param(bool & value);

        // Flow field
        FlowField flow_field;
    
        // Boids
        int BOIDS_NUM;
        vector<Boid *> boids;
        ofFbo boids_fbo;
    
        // Boids areas of fear
        vector <FearArea *> fearAreas;
        int FEAR_AREAS_NUM;
    
        // XML
        // Used for drawing settings
        ofxXmlSettings xml_settings;
    
        // JSON
        ofxJSONElement json_arguments;
    
        // Time
        float APP_RUNTIME_MS;
    
        // Debug
        const bool DEBUG_JSON = false;
};
