#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Firework.h"
#include "SandLine.h"
#include "vv_geojson.h"
#include "globals.h"
#include <time.h>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		std::string current_date_time();

		void mousePressed(int x, int y, int button);
		void keyPressed(int key);

		void play_sound_for_nation(std::string nation);
		void save_fbo(ofFbo * fbo, std::string path);

		bool show_intro_screen;
		bool final_greet;
		int arduino_digital_events_counter;

		// FBO for the 3d environment
		ofFbo threed_map_fbo;

		// ARDUINO
		ofArduino arduino;
		bool can_setup_arduino; // flag variable for setting up arduino once
		bool joystick_pressed, zoom_in_pressed, zoom_out_pressed;
    	string analog_status;
		ofVec2f joystick;

		// OSC
		ofxOscReceiver osc_receiver;
		std::string current_tweeted_city;
		std::string current_tweet_hashtags;

		// 3D
		ofEasyCam cam;
		float text_scale;
		// Firework firework;
		deque <Firework> fireworks;
		ofTexture firework_texture;

		// camera
		float cam_move_speed, cam_orient_speed;
		ofPoint cam_position;
		ofVec3f cam_move_velocity, cam_move_acceleration;
		ofVec3f cam_orientation, cam_orient_velocity, cam_orient_acceleration;
		void compute_cam_movement();
		void compute_cam_orientation();
		void cam_zoom_in();
    	void cam_zoom_out();

		// used to compute the boundary
		ofVboMesh poly_meshes_centroids; // mesh with the centroids for each polygon
		ofPoint geoshape_centroid; // overall shape centroid coordinates

		// GEOJSON
		float geojson_scale;
		ofRectangle geoshape_bb;

		//ofPoint spherical_to_cartesian(float lon, float lat, float radius);
		ofxJSONElement geojson_map;

		vector <ofVboMesh> poly_meshes; // stores the geojson shapes
		vector <vv_geojson::city> cities; // stores the extruded names of the cities

		ofTrueTypeFont font, legend_font;

		// SOUND
		ofSoundPlayer chatting_sound_en;
		ofSoundPlayer chatting_sound_jp;
		ofSoundPlayer chatting_sound_es;
		ofSoundPlayer chatting_sound_fr;
		ofSoundPlayer chatting_sound_it;
		ofSoundPlayer chatting_sound_gr;
		ofSoundPlayer chatting_sound_de;
		ofSoundPlayer thanks_sound;

		// INTERNET ARTWORK
		SandLine sand_line;
		bool save_artwork;

	// ARDUINO METHODS
	private:
    
		void setupArduino(const int & version);
		void digitalPinChanged(const int & pinNum);
		void analogPinChanged(const int & pinNum);
		void updateArduino();
};