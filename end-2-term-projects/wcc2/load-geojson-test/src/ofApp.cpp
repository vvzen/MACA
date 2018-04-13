#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // 3D
    cam.setDistance(100);


    // GEOJSON

    std::string file_path = "uk_borders_poly_simplified.geojson";

    // Now parse the JSON
    bool parsing_successful = geojson_map.open(file_path);

    if (parsing_successful){
        cout << "File " << file_path << " loaded correctly" << endl;
    }
    else {
        cout << "Failed to parse JSON" << endl;
    }

    // attempting to load each polygon
    cout << "number of polygons: " << geojson_map["features"].size() << endl;

    for (Json::ArrayIndex i = 0; i < geojson_map["features"].size(); ++i){

        // {"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[0.152421995997429,51.59897994995117],[0.148128002882061,51.5844841003418]]},"properties":{"ID_0":242,"ISO":"GBR","NAME_0":"United Kingdom","ID_1":1,"NAME_1":"England","ID_2":1,"NAME_2":"Barking and Dagenham","TYPE_2":"London Borough","ENGTYPE_2":"London Borough","NL_NAME_2":null,"VARNAME_2":null}},

        std::string type  = geojson_map["features"][i]["geometry"]["type"].asString();

        if (type == "Polygon"){
            int n_points = geojson_map["features"][i]["geometry"]["coordinates"][0].size();

            cout << "current i: " << i << ", type: " << type << ", n_points: " << n_points << endl;

            for (Json::ArrayIndex c = 0; c < n_points; ++c){
                
                float lon = geojson_map["features"][i]["geometry"]["coordinates"][0][c][0].asFloat();
                float lat = geojson_map["features"][i]["geometry"]["coordinates"][0][c][1].asFloat();

                // ofPoint point = ofPoint(
                //     geojson_map["features"][i]["geometry"]["coordinates"][0][c][0].asFloat(),
                //     geojson_map["features"][i]["geometry"]["coordinates"][0][c][1].asFloat());

                //cout << "current point, float: "<< lon << ", " << lat << endl;

                ofPoint projected = spherical_to_cartesian(lon, lat, 600);
                //cout << "current point after projection: "<< ofToString(projected) << endl;

                points_mesh.addVertex(projected);
            }
        }

        points_mesh.setMode(OF_PRIMITIVE_POINTS);
        cout << "ended parsing of file" << endl;

        // std::string author = json["response"]["docs"][i]["byline"]["original"].asString();
        // std::string date   = json["response"]["docs"][i]["pub_date"].asString();
        // std::string text   = title + " - " + author + " (" + date + ")";
        // ofDrawBitmapString(text, 20, i * 24 + 40);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofSetColor(255);
    ofFill();

    ofEnableDepthTest();

    cam.begin();

    // ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);

    ofDrawSphere(0, 0, 3, 3);
    ofDrawGrid();

    points_mesh.draw();
    // for (int i = 0; i < poly_points.size(); i++){
    //     ofPushMatrix();
    //     ofTranslate(poly_points.at(i).x, poly_points.at(i).y, poly_points.at(i).z);
    //     ofDrawSphere(0, 0, 0.25, 0.25);
    //     ofPopMatrix();
    // }

    cam.end();

    ofDisableDepthTest();
}

//--------------------------------------------------------------
ofPoint ofApp::spherical_to_cartesian(float lon, float lat, float radius){

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
// ofPoint ofApp::mercator(float lon, float lat) {
//     ofPoint position;
//     position.x = (lon / 180.0) * scale + translateX;
//     position.y = /*_coordinate.latitude > 85 ? 1 : _coordinate.latitude < -85 ? -1 //<- we should consider about polar regions converting..
//     : */ ( log(tan(PI / 4.0 + pvRadians(lat) / 2.0)) / PI ) * scale - translateY;
//     return position;
// };

// //--------------------------------------------------------------
// float ofApp::pvRadians(float degrees) {
//     float radians = PI / 180.0;
//     return radians * _degrees;
// };