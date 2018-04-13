#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);
		void keyPressed(int key);

		ofPoint spherical_to_cartesian(float lon, float lat, float radius);

		ofEasyCam cam;

		// used to compute the boundary
		ofVboMesh poly_meshes_centroids; // mesh with the centroids for each polygon
		ofPoint geoshape_centroid; // overall shape centroid coordinates
		ofVec3f overall_rotation;

		float geojson_scale;

		ofxJSONElement geojson_map;

		vector <ofVboMesh> poly_meshes;
};
