#pragma once

#include "ofMain.h"
#include "FboSource.h"

class MovingRectSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void drawMovingRect(int, int, int, int);
        void setName(string _name);
        void setColor(ofColor);
        ofColor rectColor;
};
