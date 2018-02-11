#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxPS3EyeGrabber.h"
#include "ofxDelaunay.h"
#include "ofxImGui.h"
#include "ThemeTest.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	// events
	void keyPressed(int key);

	vector <ofPoint> get_triangle_points(ofxDelaunay & triangulation, int i);

	ofVideoGrabber video;
	ofxCvColorImage image;

	ofxCvGrayscaleImage grayImage;
	ofxCvGrayscaleImage inverted;
	ofxCvGrayscaleImage blurred;
	ofxCvGrayscaleImage mask;

    vector<cv::Point2f> corners;

	ofxDelaunay triangulation;
	bool debug;

	// GUI
	void drawImGui();
	ofxImGui::Gui gui;
	float GUI_threshold;
	float GUI_max_distance;
	float GUI_bg_alpha;
	int GUI_max_points;
};

