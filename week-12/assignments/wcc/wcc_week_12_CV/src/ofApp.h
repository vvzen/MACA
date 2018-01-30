#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	ofVideoGrabber video;		//Declare the video player object
	// ofVideoPlayer video;		//Declare the video player object

	ofxCvColorImage image;
	ofxCvGrayscaleImage grayImage;
	ofxCvGrayscaleImage blurred;
	ofxCvGrayscaleImage background;
	ofxCvGrayscaleImage diff;
	ofxCvGrayscaleImage mask;

	ofxCvContourFinder 	contourFinder;

    vector<ofxCvBlob>  blobs;
    bool debug;

	ofPolyline snake;

	// EVENTS
	void mousePressed(int x, int y, int button);
	void keyPressed(int button);
};

