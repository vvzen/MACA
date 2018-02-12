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

        int popmax;
        float mutationRate;
        Population population;
        ofVideoGrabber vidGrabber;
        ofImage target;
        bool activate;
};
