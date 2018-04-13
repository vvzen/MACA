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
    cout << "number of total polygons: " << geojson_map["features"].size() << endl;

    for (Json::ArrayIndex i = 0; i < geojson_map["features"].size(); ++i){

        // {"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[0.152421995997429,51.59897994995117],[0.148128002882061,51.5844841003418]]},"properties":{"ID_0":242,"ISO":"GBR","NAME_0":"United Kingdom","ID_1":1,"NAME_1":"England","ID_2":1,"NAME_2":"Barking and Dagenham","TYPE_2":"London Borough","ENGTYPE_2":"London Borough","NL_NAME_2":null,"VARNAME_2":null}},
        
        ofxJSONElement coordinates = geojson_map["features"][i]["geometry"]["coordinates"];

        std::string type  = geojson_map["features"][i]["geometry"]["type"].asString();
        
        if (type == "Polygon"){

            // we need to start a new ofVboMesh
            ofVboMesh mesh;

            int n_points = coordinates[0].size();

            //cout << "current i: " << i << ", type: " << type << ", n_points: " << n_points << endl;

            for (Json::ArrayIndex j = 0; j < n_points; ++j){
                
                float lon = coordinates[0][j][0].asFloat();
                float lat = coordinates[0][j][1].asFloat();

                //cout << "current point, float: "<< lon << ", " << lat << endl;

                ofPoint projected = spherical_to_cartesian(lon, lat, 100);
                //cout << "current point after projection: "<< ofToString(projected) << endl;

                mesh.addVertex(projected);
                mesh.addColor(ofFloatColor(1.0, 1.0, 1.0));
            }
            mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
            poly_meshes.push_back(mesh);
        }
        else if (type == "MultiPolygon"){
            
            int n_polygons = coordinates.size();

            cout << "current i: " << i << ", type: " << type << ", n_polygons: " << n_polygons << endl;
            
            for (Json::ArrayIndex k = 0; k < n_polygons; ++k){
                
                ofVboMesh mesh;

                int n_points = coordinates[k][0].size();

                for (Json::ArrayIndex j = 0; j < n_points; ++j){
                    float lon = coordinates[k][0][j][0].asFloat();
                    float lat = coordinates[k][0][j][1].asFloat();

                    ofPoint projected = spherical_to_cartesian(lon, lat, 100);
                    //cout << "current point after projection: "<< ofToString(projected) << endl;

                    mesh.addVertex(projected);
                    mesh.addColor(ofFloatColor(1.0, 1.0, 1.0));
                    mesh.addIndex(j);
                }
                mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
                // mesh.setMode(OF_PRIMITIVE_POINTS);
                poly_meshes.push_back(mesh);
            }
        }
    }
    cout << "ended parsing of file" << endl;
    cout << "poly_meshes.size(): " << poly_meshes.size() << endl;
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

    for (int i = 0; i < poly_meshes.size(); i++){
        poly_meshes.at(i).drawWireframe();
    }
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