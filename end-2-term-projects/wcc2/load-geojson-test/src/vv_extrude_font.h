#pragma once
#include "ofMain.h"

// this method extrudes in 3D the given string and returns a vector of ofVboMesh-es.
// if get_front_only is true only the front face will be returned, instead of the back and sides (I added this mode since I was getting a low framerate)
vector<ofVboMesh> extrude_mesh_from_text(string word, ofTrueTypeFont & font, float extrusion_depth, float scale, bool get_front_only);

vector<vector<vector <ofPoint>>> get_string_as_3d_point_matrix(ofTrueTypeFont & font, string s, int num_of_samples);
vector <ofPath> get_string_as_sampled_points(ofTrueTypeFont & font, string s, int num_of_samples);