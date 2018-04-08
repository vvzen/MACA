#pragma once

#include "ofMain.h"
#include "ofxAruco.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawMarker(float size, const ofColor & color);
    
		void keyPressed  (int key);
		
		ofVideoGrabber grabber;
		ofVideoPlayer player;

		ofBaseVideoDraws * video;

		ofxAruco aruco;
		bool useVideo;
		bool showMarkers;
		bool showBoard;
		bool showBoardImage;
		ofImage board;
		ofImage marker;
        ofImage img;


		void setupSolarSystem();
		void drawSolarSystem();
		
		ofSpherePrimitive earth, moon, mars, sun;
		ofMaterial sunMat, planetMat;
		ofImage earthTex,sunTex;


};
