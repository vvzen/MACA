#include "ofMain.h"
#include "ofxJSON.h"
#include "vv_map_projections.h"

namespace vv_geojson {

    ofPoint create_world_map(std::string path, vector<ofVboMesh> & poly_meshes, float scale);
}