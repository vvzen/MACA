#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Firework.h"
#include "vv_geojson.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);
		void keyPressed(int key);

		// ARDUINO
		ofArduino arduino;
		bool can_setup_arduino; // flag variable for setting up arduino once
		bool joystick_pressed;
    	string analog_status;
		ofVec2f joystick;

		// OSC
		ofxOscReceiver osc_receiver;
		std::string current_tweeted_city;

		// 3D
		ofEasyCam cam;
		ofPoint cam_position;
		ofVec3f cam_move_velocity, cam_move_acceleration;
		ofVec3f cam_orientation, cam_orient_velocity, cam_orient_acceleration;
		float cam_move_speed, cam_orient_speed;
		float text_scale;
		// Firework firework;
		deque <Firework> fireworks;
		ofTexture firework_texture;

		void compute_cam_movement();
		void compute_cam_orientation();

		ofLight key_light_1;

		// used to compute the boundary
		ofVboMesh poly_meshes_centroids; // mesh with the centroids for each polygon
		ofPoint geoshape_centroid; // overall shape centroid coordinates
		ofVec3f overall_rotation;

		// GEOJSON
		float geojson_scale;

		//ofPoint spherical_to_cartesian(float lon, float lat, float radius);
		ofxJSONElement geojson_map;

		vector <ofVboMesh> poly_meshes; // stores the geojson shapes
		vector <vv_geojson::city> cities; // stores the extruded names of the cities

		ofTrueTypeFont font;

	// ARDUINO METHODS
	private:
    
		void setupArduino(const int & version);
		void digitalPinChanged(const int & pinNum);
		void analogPinChanged(const int & pinNum);
		void updateArduino();
};
