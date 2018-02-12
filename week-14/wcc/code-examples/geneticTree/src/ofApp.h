#pragma once
#include "ofMain.h"
#include "Forrest.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
        void displayInfo();

        int popmax;
        float mutationRate;
        Forrest forrest;
        bool activate;
};
