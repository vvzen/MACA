#include "ofMain.h"
#include "ofxJSON.h"
#include "vv_extrude_font.h"
#include "vv_map_projections.h"
#include <regex>

namespace vv_geojson {

    struct city {
        std::string name;
        vector <ofVboMesh> meshes;
        ofPoint position;
    };

    ofPoint create_geojson_map(std::string path, ofTrueTypeFont & font, vector<ofVboMesh> & poly_meshes, vector<city> & cities_meshes,  float scale);

}