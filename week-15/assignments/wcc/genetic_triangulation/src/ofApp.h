#pragma once

#include "ofMain.h"
#include "Population.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void displayInfo();

		ofImage painting;

		// triangulation stuff
		vector <ofPoint> get_triangle_points(ofxDelaunay & triangulation, int i);
		vector<ofPoint> points;
		
		//int num_points;
		bool activate;
		int popmax;
        float mutation_rate;

		// genetic stuff
		Population population;
		
};
