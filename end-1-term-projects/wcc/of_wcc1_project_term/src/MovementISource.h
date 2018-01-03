#pragma once

#include "ofMain.h"
#include "FboSource.h"

class MovementISource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();

        void setName(string);
        void setupBalls();
        void updateBalls();
        void reset();

        bool show_calibration_grid;

        ofImage reference_image;

        void drawCalibrationGrid(int numOfLines);
        // 1
        void drawFlashingIntro(int & time_multiplier);
        // 2
        void drawMovingLines(float currentShowTime);
        // events
        void onKeyPressed(ofKeyEventArgs & event);

        // timing
        float show_start_time;
        float current_show_time;
        bool CHECKPOINT_1 = true;
        // determines the timing of the intro rectangles
        int intro_time_multiplier;
        bool CHECKPOINT_2 = false;
        float lines_start_time;
        bool lines_started = false;
        float rects_start_time;
        bool rects_started = false;

        // used to keep track of the timing of the rectangles
        bool rectangle_triggers[6] = {false, false, false, false, false, false};
};
