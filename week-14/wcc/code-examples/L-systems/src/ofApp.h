#pragma once
#include "ofMain.h"
#include "Rule.h"
#include "LSystem.h"
#include "Turtle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void mousePressed(int x, int y, int button);

		LSystem lsys;
        vector<Rule> ruleset; // The ruleset (an array of Rule objects)
        Turtle turtle;
};
