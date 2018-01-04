#pragma once

#include "ofMain.h"
#include "FboSource.h"

class BouncingBallsSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string);
        void setupBalls();
        void updateBalls();
        void reset();
        void drawBalls(int x, int y, int w, int h);

        vector <ofVec2f> locations;
        vector <ofVec2f> speeds;

        int startTime;
        ofColor ballColor;
};
