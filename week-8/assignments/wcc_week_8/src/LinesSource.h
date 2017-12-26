#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "Line.h"

#define DISTANCE_THRESHOLD 40
#define DEBUG 0

class LinesSource : public ofx::piMapper::FboSource {
    
	public:
        void setup();
		void update();
		void draw();
        void setName(string _name);
    
    // CUSTOM STUFF
    
    vector <Line> lines;
    // displacer agents
    ofVec2f fear;
    ofVec2f attraction;
};
