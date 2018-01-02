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
        void drawFlashingIntro(int & time_multiplier);
        void onKeyPressed(ofKeyEventArgs & event);

        // determines the timing of the intro rectangles
        int intro_time_multiplier;

        float start_time;
        // used to keep track of the timing of the rectangles
        bool rectangle_triggers[6] = {false, false, false, false, false, false};
};
