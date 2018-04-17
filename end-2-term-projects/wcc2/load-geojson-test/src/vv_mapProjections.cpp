#include "vv_mapProjections.h"

//--------------------------------------------------------------
ofPoint vvMapProjections::spherical_to_cartesian(float lon, float lat, float radius){

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
ofPoint vvMapProjections::mercator(float lon, float lat, float scale){
    
    ofVec2f offset = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);

    scale = ofGetWidth() / (2 * PI);

    ofPoint position;

    position.x = (lon / 180) * scale - 0;
    // this is pure black magic I don't know anything about it
    position.y = (log(tan(PI / 4.0 + ofDegToRad(lat) / 2.0)) / PI) * scale - 0;
    return position;
}