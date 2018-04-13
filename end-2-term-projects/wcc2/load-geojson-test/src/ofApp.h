#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofEasyCam cam;

		// ofPoint mercator(float lon, float lat);
		ofPoint spherical_to_cartesian(float lon, float lat, float radius);
		// float pvRadians(float degrees);

		ofxJSONElement geojson_map;

		vector <ofVboMesh> poly_meshes;
		ofVboMesh points_mesh;
};
