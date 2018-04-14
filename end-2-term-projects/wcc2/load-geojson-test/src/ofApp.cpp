#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // TYPE
    font.load("fonts/AndaleMono.ttf", 16, true, true, true);

    // 3D
    cam.setDistance(40);
    cam.setNearClip(2);

    geoshape_centroid = ofPoint(0, 0, 0);
    overall_rotation = ofVec3f(130, -6, -78);

    // GEOJSON

    geojson_scale = 200;

    // std::string file_path = "uk_borders_poly_simplified.geojson";
    std::string file_path = "uk_borders_and_cities.geojson";

    // Now parse the JSON
    bool parsing_successful = geojson_map.open(file_path);

    if (parsing_successful){
        cout << "File " << file_path << " loaded correctly" << endl;
    }
    else {
        cout << "Failed to parse JSON" << endl;
    }

    // load each polygon from the geojson
    cout << "number of total polygons: " << geojson_map["features"].size() << endl;

    // todo: compute boundaries of the whole current feature
    for (Json::ArrayIndex i = 0; i < geojson_map["features"].size(); ++i){

        // {"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[0.152421995997429,51.59897994995117],[0.148128002882061,51.5844841003418]]},"properties":{"ID_0":242,"ISO":"GBR","NAME_0":"United Kingdom","ID_1":1,"NAME_1":"England","ID_2":1,"NAME_2":"Barking and Dagenham","TYPE_2":"London Borough","ENGTYPE_2":"London Borough","NL_NAME_2":null,"VARNAME_2":null}},
        
        ofxJSONElement coordinates = geojson_map["features"][i]["geometry"]["coordinates"];

        std::string type  = geojson_map["features"][i]["geometry"]["type"].asString();

        if (type == "Point"){
            float lon = coordinates[0].asFloat();
            float lat = coordinates[1].asFloat();

            std::string city_name = geojson_map["features"][i]["properties"]["name"].asString();
            // std::replace(city_name.begin(), city_name.end(), ' ', '_');

            cout << "current city: " << city_name << endl;

            // I'm excluding those ones for aesthetic reasons
            if (city_name != "City of Westminster" && city_name != "City of London"){
                
                ofPoint projected = spherical_to_cartesian(lon, lat, geojson_scale);

                vector<ofVboMesh> city_name_meshes = extrude_mesh_from_text(city_name, font, 3);
                city current_city;
                current_city.meshes = city_name_meshes;
                current_city.position = projected;
                current_city.name = city_name;
                cities_names_meshes.push_back(current_city);
            }
        }
        else if (type == "Polygon"){

            // we need to start a new ofVboMesh
            ofVboMesh mesh;

            int n_points = coordinates[0].size();

            //cout << "current i: " << i << ", type: " << type << ", n_points: " << n_points << endl;

            for (Json::ArrayIndex j = 0; j < n_points; ++j){
                
                float lon = coordinates[0][j][0].asFloat();
                float lat = coordinates[0][j][1].asFloat();

                //cout << "current point, float: "<< lon << ", " << lat << endl;

                ofPoint projected = spherical_to_cartesian(lon, lat, geojson_scale);
                //cout << "current point after projection: "<< ofToString(projected) << endl;

                mesh.addVertex(projected);
                mesh.addColor(ofFloatColor(1.0, 1.0, 1.0));
            }
            mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
            poly_meshes.push_back(mesh);

            ofPoint mesh_centroid = mesh.getCentroid();

            poly_meshes_centroids.addVertex(mesh_centroid);
            poly_meshes_centroids.addColor(ofFloatColor(1.0, 0.0, 0.0));

            geoshape_centroid += mesh_centroid;
        }
        else if (type == "MultiPolygon"){
            
            int n_polygons = coordinates.size();

            //cout << "current i: " << i << ", type: " << type << ", n_polygons: " << n_polygons << endl;
            
            for (Json::ArrayIndex k = 0; k < n_polygons; ++k){
                
                ofVboMesh mesh;

                int n_points = coordinates[k][0].size();

                for (Json::ArrayIndex j = 0; j < n_points; ++j){
                    float lon = coordinates[k][0][j][0].asFloat();
                    float lat = coordinates[k][0][j][1].asFloat();

                    ofPoint projected = spherical_to_cartesian(lon, lat, geojson_scale);
                    //cout << "current point after projection: "<< ofToString(projected) << endl;
                    
                    mesh.addVertex(projected);
                    mesh.addColor(ofFloatColor(1.0, 1.0, 1.0));
                    mesh.addIndex(j);
                }
                mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
                // mesh.setMode(OF_PRIMITIVE_POINTS);
                poly_meshes.push_back(mesh);

                ofPoint mesh_centroid = mesh.getCentroid();

                poly_meshes_centroids.addVertex(mesh_centroid);
                poly_meshes_centroids.addColor(ofFloatColor(0.0, 0.0, 1.0));

                geoshape_centroid += mesh_centroid;
            }
        }
    }
    
    poly_meshes_centroids.setMode(OF_PRIMITIVE_POINTS);
    // cities_mesh.setMode(OF_PRIMITIVE_POINTS);

    // set the overall geoshape centroid
    // making an average of the centroids
    geoshape_centroid /= poly_meshes_centroids.getNumVertices();

    cout << "overall centroid: " << geoshape_centroid << endl;

    cout << "ended parsing of file" << endl;
    cout << "poly_meshes.size(): " << poly_meshes.size() << endl;
    cout << "cities_names_meshes.size(): " << cities_names_meshes.size() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofSetColor(255);
    ofFill();

    glPointSize(5);

    ofEnableDepthTest();

    // cam.lookAt(geoshape_centroid);
    cam.begin();

    ofDrawAxis(100);

    // rotate the geoshape so that it faces us
    ofRotateX(overall_rotation.x);
    ofRotateY(overall_rotation.y);
    ofRotateZ(overall_rotation.z);
    // move shape to the center of the world
    ofTranslate(-geoshape_centroid);

    // draw the vbo meshes for the polygons
    for (int i = 0; i < poly_meshes.size(); i++){
        poly_meshes.at(i).draw();
    }

    // draw the text of each city
    for (int i = 0; i < cities_names_meshes.size(); i++){
        ofPushMatrix();
            ofTranslate(cities_names_meshes.at(i).position);
            ofRotateZ(69.082);
            ofRotateX(95);
            ofRotateZ(-6.67969);
            ofScale(0.01, 0.01, 0.01);
            for (int m = 0; m < cities_names_meshes.at(i).meshes.size(); m++){
                cities_names_meshes.at(i).meshes.at(m).draw();
            }
        ofPopMatrix();
    }

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
void ofApp::mousePressed(int x, int y, int button){
    cout << "ofMap(mouseX, 0, ofGetWidth(), -90, 90): " << ofMap(mouseX, 0, ofGetWidth(), -90, 90) << endl;
    cout << "overall_rotation: " << overall_rotation << endl;
    cout << "cam properties" << endl;
    cout << "cam.getGlobalPosition():    " << cam.getGlobalPosition() << endl;
    cout << "cam.getGlobalOrientation(): " << cam.getGlobalOrientation() << endl;
    cout << "cam.getDistance():          " << cam.getDistance() << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key){
        case 'q':{
            overall_rotation.x -= 1.0;
            break;
        }
        case 'w':{
            overall_rotation.x += 1.0;
            break;
        }
        case 'a':{
            overall_rotation.y -= 1.0;
            break;
        }
        case 's':{
            overall_rotation.y += 1.0;
            break;
        }
        case 'z':{
            overall_rotation.z -= 1.0;
            break;
        }
        case 'x':{
            overall_rotation.z += 1.0;
            break;
        }
    }

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