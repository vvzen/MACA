#pragma once
/*
 --------------- ATTENTION --------------
 Before running the project, fix a small ofxOpenCv bug.
 
 Currently the operation image = &iplImage raises error, if the image is not allocated.
 To fix it, open the addon's file addons/ofxOpenCv/src/ofxCvImage.cpp
 and find the following function definition:
 void ofxCvImage::operator = ( const IplImage* mom )
 In this function body, replace line
	if( mom->nChannels == cvImage->nChannels && mom->depth == cvImage->depth ){
 with the following line:
	if( !bAllocated || ( mom->nChannels == cvImage->nChannels && mom->depth == cvImage->depth ) ){
 
 (Note, without this fix, the following example lines flowX = &iplX; and flowY = &iplY;
 can raise runtime error)
 */
#include "ofMain.h"
#include "ofxOpenCv.h"
using namespace cv;

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

    ofVideoGrabber video;
	bool calculatedFlow;

	ofxCvColorImage currentColor;		//First and second original images
	ofxCvGrayscaleImage gray1, gray2;	//Decimated grayscaled images
	ofxCvFloatImage flowX, flowY;		//Resulted optical flow in x and y axes
};
