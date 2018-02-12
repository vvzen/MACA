#pragma once
#include "ofMain.h"
#include "Population.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void displayInfo();

        string target;
        int popmax;
        float mutationRate;
        Population population;
};
