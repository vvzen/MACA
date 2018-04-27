#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "globals.h"
#include "vv_map_projections.h"
#include "vv_geojson.h"

struct InfluencePoint {
	std::string name;
	ofPoint pos;
	long population;
	float weight;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);

		void generate_mesh(int num_cols, int num_rows, float frequency, float amplify_factor, ofMesh &borders_mesh, vector<InfluencePoint> &influence_points);
		void drawImGui();

		// CSV
		ofVec3f load_points_from_csv(std::string path, ofVboMesh &influence_mesh, vector<InfluencePoint> &influence_points, float scale);

		// 3D
		of3dPrimitive waves_primitive; // the actual wavy mesh
		ofVboMesh influence_points_mesh; // a series of influence points stored in a mesh
		ofVboMesh border_points_mesh; // the actual borders of the wavy mesh
		vector <ofVboMesh> world_meshes; // a vector containing the meshes of the world
		ofEasyCam cam;
		ofLight light;

		vector <InfluencePoint> influence_points;
		int num_random_points;

		// GUI
		ofxImGui::Gui gui;
		int GUI_res_x, GUI_res_y;
		int GUI_num_random_points;
		float GUI_frequency, GUI_amp_factor, GUI_weight_multiplier;
		float GUI_falloff_decay;
		bool GUI_draw_wireframe;
		bool GUI_draw_target_points;
		bool GUI_draw_world_meshes;
};
