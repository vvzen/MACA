#pragma once

#include "ofMain.h"
#include "FboSource.h"

#define EXHIBITION_TIME 135 // this value must mutch the one inside the scenes.json

class VVSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();

        void setName(string);
        void reset();

        bool show_calibration_grid;

        ofImage reference_image;

        void drawCalibrationGrid(int numOfLines);
        // checkpoint 1
        void drawFlashingIntro(int & time_multiplier, float currentShowTime);
        // checkpoint 2
        void drawMovingLines(float currentShowTime);
        // checkpoint 3
        void drawFadingQuads(float currentShowTime);
        // checkpoint 4
        void drawColouredLines(float currentShowTime);
        // events
        void onKeyPressed(ofKeyEventArgs & event);

        // initialisation
        void init_vars();

        // timing
        float show_start_time;
        float current_show_time;
        
        // checkpoints related vars
        bool CHECKPOINT_1;
        // determines the timing of the intro rectangles
        float intro_checkpoints[7];
        int intro_time_multiplier;
        bool intro_started;
        float intro_start_time;

        // checkpoint 2
        bool CHECKPOINT_2;
        float lines_start_time;
        bool lines_started;
        float rects_start_time;
        bool rects_started;

        // checkpoint 3
        bool CHECKPOINT_3;
        float bars_start_time;
        bool bars_started;
        bool show_left_ellipse;
        bool white_quads_started;
        bool white_quads_ended;
        float white_quads_start_time;
        float black_quads_start_time;
        bool black_quads_ended;
        float v_lines_start_time;

        ofVec2f center_rect_size;
        float circles_size_multiplier;
        float quad_size; 

        // checkpoint 4
        bool CHECKPOINT_4;
        float coloured_lines_start_time;
        bool coloured_lines_started;
        float black_bg_fade_in_time;
        bool bg_started_fade;
        bool coloured_quads_started;
        float coloured_quads_start_time;

        int num_rects_h_1;
        int num_rects_h_2;
        int num_rects_h_3;
        int num_rects_h_4;
        vector<ofColor> final_quads_colors;
        int num_x_quads;
        int num_y_quads;

        // used to keep track of the timing of the rectangles
        bool rectangle_triggers[6];
};
