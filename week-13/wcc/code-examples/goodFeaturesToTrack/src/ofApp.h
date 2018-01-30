#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
using namespace cv;

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	ofVideoGrabber video;		//Declare the video player object
	ofxCvColorImage image;

	ofxCvGrayscaleImage grayImage;
	ofxCvGrayscaleImage inverted;
	ofxCvGrayscaleImage blurred;
	ofxCvGrayscaleImage mask;

    vector<Point2f> corners;
};

