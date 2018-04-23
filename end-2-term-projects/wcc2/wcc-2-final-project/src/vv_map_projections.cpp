#include "globals.h"
#include "vv_map_projections.h"

//--------------------------------------------------------------
ofPoint vv_map_projections::spherical_to_cartesian(float lon, float lat, float radius){

    float latitude = ofDegToRad(lat);
    float longitude = ofDegToRad(lon);

    ofPoint position = ofPoint(
        radius * sin(latitude) * cos(longitude),
        radius * sin(latitude) * sin(longitude),
        radius * cos(latitude)
    );

    return position;
}

//--------------------------------------------------------------
// taken and edited from the ofxGeoJSON addon by moxuse
//--------------------------------------------------------------
ofPoint vv_map_projections::mercator(float lon, float lat, float scale){
    
    ofVec2f offset = ofVec2f(WIDTH / 2, HEIGHT / 2);

    scale = WIDTH / (2 * PI);

    ofPoint position;

    position.x = (lon / 180) * scale - 0;
    // this is pure black magic I don't know anything about it
    position.y = (log(tan(PI / 4.0 + ofDegToRad(lat) / 2.0)) / PI) * scale - 0;
    return position;
}