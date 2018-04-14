#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "vv_extrudeFont.h"

struct city {
	std::string name;
	vector <ofVboMesh> meshes;
	ofPoint position;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);
		void keyPressed(int key);

		ofPoint spherical_to_cartesian(float lon, float lat, float radius);

		ofEasyCam cam;
		ofPoint cam_position;
		ofVec3f cam_move_velocity, cam_move_acceleration;
		ofVec3f cam_orientation, cam_orient_velocity, cam_orient_acceleration;
		float cam_move_speed, cam_orient_speed;

		void compute_cam_movement();
		void compute_cam_orientation();

		// used to compute the boundary
		ofVboMesh poly_meshes_centroids; // mesh with the centroids for each polygon
		ofPoint geoshape_centroid; // overall shape centroid coordinates
		ofVec3f overall_rotation;

		float geojson_scale;

		ofxJSONElement geojson_map;

		vector <ofVboMesh> poly_meshes;
		vector <city> cities_names_meshes;

		ofTrueTypeFont font;
};
