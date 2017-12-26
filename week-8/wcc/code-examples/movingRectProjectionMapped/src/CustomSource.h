#pragma once

#include "ofMain.h"
#include "FboSource.h"

class CustomSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string _name);

		vector <ofRectangle> rects;
		vector <float> rectSpeeds;
};
