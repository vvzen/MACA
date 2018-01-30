#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

        ofImage img, croppedImg;
		ofVideoGrabber videoGrabber;
		ofxCvHaarFinder finder;
        ofxCvColorImage cvImg;		//The current video frame
        ofxCvGrayscaleImage cvGrayImage;
        ofxCvFloatImage cvFloatImg, cvSumImage, cvAvgImage, cvCounterImg;
        float faceCounter;
        ofRectangle cur;
        void mousePressed(int x, int y, int button);
        void keyPressed(int key);
};
