#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void setupSolarSystem();
		void drawSolarSystem();
		
		ofSpherePrimitive earth, moon, mars, sun;
		ofVec3f earthLoc;
		ofEasyCam cam;
		ofLight light;
		ofMaterial sunMat, planetMat;
		ofImage earthTex;

		ofMesh starsMesh;
};
