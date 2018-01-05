#pragma once

#include "ofMain.h"
#include "FboSource.h"

class MovementISource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();

        void setName(string);
        void reset();

        bool show_calibration_grid;

        ofImage reference_image;

        void drawCalibrationGrid(int numOfLines);
        // 1
        void drawFlashingIntro(int & time_multiplier);
        // 2
        void drawMovingLines(float currentShowTime);
        // 3
        void drawMovingCircles(float currentShowTime);
        // 4
        void drawColouredLines(float currentShowTime);
        // events
        void onKeyPressed(ofKeyEventArgs & event);

        // initialisation
        void init_vars();

        // timing
        float show_start_time;
        float current_show_time;
        bool CHECKPOINT_1 = false;
        // determines the timing of the intro rectangles
        int intro_time_multiplier;
        bool CHECKPOINT_2 = false;
        float lines_start_time;
        bool lines_started = false;
        float rects_start_time;
        bool rects_started = false;
        bool CHECKPOINT_3 = false;
        float bars_start_time;
        bool bars_started = false;
        bool show_left_ellipse = false;
        bool ball_disappeared = false;
        bool CHECKPOINT_4 = false;
        float coloured_lines_start_time;
        bool coloured_lines_started = false;
        float white_bg_fade_in_time;
        bool bg_started_fade = false;

        // checkpoint 3
        ofVec2f center_rect_size;
        ofVec2f ellipse_1_pos;
        ofVec2f ellipse_2_pos;
        ofVec2f ellipse_velocity;
        ofVec2f ellipse_acceleration;
        float circles_size_multiplier;
        unsigned int bounce_count;

        // checkpoint 4
        int num_rects_h_1;
        int num_rects_h_2;
        int num_rects_h_3;
        int num_rects_h_4;

        // used to keep track of the timing of the rectangles
        bool rectangle_triggers[6] = {false, false, false, false, false, false};
};
