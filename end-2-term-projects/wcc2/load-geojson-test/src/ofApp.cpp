#include "ofApp.h"
#include <chrono>
#include <thread> // for sleeping

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
	ofSetFrameRate(60);

    // TYPE
    font.load("fonts/AndaleMono.ttf", 16, true, true, true);

    // ARDUINO
    joystick = ofVec2f(0, 0);
    joystick_pressed = false;
    arduino.connect("/dev/tty.usbmodem1421", 57600);
    can_setup_arduino = false;

    // listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setup_arduino()
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	can_setup_arduino = false;

    // OSC
    current_tweeted_city = "";
    osc_receiver.setup(9000);

    // 3D
    geoshape_centroid = ofPoint(0, 0, 0);
    overall_rotation = ofVec3f(130, -6, -78);

    // LIGHTS
    // key_light_1.setAttenuation(1.0f, 0.f, 0.001f);
    key_light_1.setDirectional();

    // CAMERA
    cam.setDistance(40);
    cam.setNearClip(0.5);
    // camera placement settings
    // movement
    cam_move_speed = 0.035f;
    cam_position = ofPoint(2.38566, -19.6323, 29.135);
    cam_move_velocity = ofVec3f(0, 0, 0);
    cam_move_acceleration = ofVec3f(0, 0, 0);
    // orientation
    cam_orient_speed = 0.05f;
    cam_orientation = ofVec3f(31, 0, 0);
    cam_orient_velocity = ofVec3f(0, 0, 0);
    cam_orient_acceleration = ofVec3f(0, 0, 0);

    // GEOJSON

    geojson_scale = 200;

    std::string file_path = "uk_borders_and_cities.geojson";

    // Parse the JSON
    bool parsing_successful = geojson_map.open(file_path);

    if (parsing_successful){
        cout << "File " << file_path << " loaded correctly" << endl;
    }
    else {
        cout << "Failed to parse JSON" << endl;
    }

    cout << "number of total polygons: " << geojson_map["features"].size() << endl;

    // load each feature from the geojson
    for (Json::ArrayIndex i = 0; i < geojson_map["features"].size(); ++i){

        ofxJSONElement coordinates = geojson_map["features"][i]["geometry"]["coordinates"];
        // current geojson feature type
        // currently supported: Point, Polygon, MultiPolygon
        std::string type  = geojson_map["features"][i]["geometry"]["type"].asString();

        if (type == "Point"){
            float lon = coordinates[0].asFloat();
            float lat = coordinates[1].asFloat();

            std::string city_name = geojson_map["features"][i]["properties"]["name"].asString();

            // cout << "current city: " << city_name << endl;

            // I'm excluding those ones for aesthetic reasons
            if (city_name != "City of Westminster" && city_name != "City of London"){
                
                ofPoint projected = spherical_to_cartesian(lon, lat, geojson_scale);

                // make lowercase and prepend hashtag to city name
                std::transform(city_name.begin(), city_name.end(), city_name.begin(), ::tolower);
                city_name = "#" + city_name;

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
                mesh.addColor(ofFloatColor(0.7));
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
                    mesh.addColor(ofFloatColor(0.7));
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

    updateArduino();
    compute_cam_movement();
    compute_cam_orientation();

    // check for osc messages
	while(osc_receiver.hasWaitingMessages()){
        ofxOscMessage m;
        osc_receiver.getNextMessage(m);
        if(m.getAddress() == "/twitter-app"){
			current_tweeted_city = m.getArgAsString(0);
		}
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofSetColor(255);
    ofFill();

    glPointSize(5);

    ofEnableDepthTest();

    cam.setPosition(cam_position); // see compute_cam_movement()
    cam.setOrientation(cam_orientation);

    cam.begin();
    
    key_light_1.enable();
    key_light_1.setOrientation(cam_orientation);

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
            ofTranslate(0, 0, -0.1f);
            // ofRotateZ(69.082);
            // ofRotateX(88);
            // // ofRotateZ(-20.5664);
            // ofRotateZ(3.75);
            ofRotateX(90);
            ofRotateZ(-49.7461);
            ofRotateY(76.75);
            ofScale(0.01, 0.01, 0.01);
            for (int m = 0; m < cities_names_meshes.at(i).meshes.size(); m++){
                cities_names_meshes.at(i).meshes.at(m).draw();
            }
        ofPopMatrix();
    }

    cam.end();
    key_light_1.disable();

    ofDisableDepthTest();

    // 2D STUFF

    ofSetColor(255);
    ofFill();
    ofDrawBitmapString(current_tweeted_city, 20, 30);
    if (!can_setup_arduino){
        ofDrawBitmapString("arduino not ready...\n", 20, 50);
    }
    else {
        if (joystick_pressed) ofDrawBitmapString("joystick pressed!", 20, 70);
        ofDrawBitmapString(analog_status, 20, 90);
    }
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
void ofApp::compute_cam_movement(){

    // add joystick acceleration
    cam_move_acceleration += joystick;

    float max_speed = 0.21f;
    
    ofVec3f friction = cam_move_velocity;
    friction.normalize();
    friction *= -1;
    friction *= 0.003f;

    cam_move_velocity += cam_move_acceleration;
    
    cam_move_velocity += friction;
    cam_move_velocity *= 0.975f;
    cam_move_velocity.limit(max_speed);
    if (cam_move_velocity.length() < 0.0009f){
        cam_move_velocity = ofVec3f(0, 0, 0);
    }
    // update position
    cam_position += cam_move_velocity;
    // reset acceleration
    cam_move_acceleration = ofVec3f(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::compute_cam_orientation(){

    float max_speed = 0.21f;
    
    ofVec3f friction = cam_orient_velocity;
    friction.normalize();
    friction *= -1;
    friction *= 0.003f;

    cam_orient_velocity += cam_orient_acceleration;
    
    cam_orient_velocity += friction;
    cam_orient_velocity *= 0.975f;
    cam_orient_velocity.limit(max_speed);
    // after a certain speed threshold, save computing time by remaining still
    if (cam_orient_velocity.length() < 0.0009f){
        cam_orient_velocity = ofVec3f(0, 0, 0);
    }
    // update position
    cam_orientation += cam_orient_velocity;
    // reset acceleration
    cam_orient_acceleration = ofVec3f(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    cout << "ofMap(mouseX, 0, ofGetWidth(), -90, 90): " << ofMap(mouseX, 0, ofGetWidth(), -90, 90) << endl;
    cout << "ofMap(mouseY, 0, ofGetHeight(), -90, 90): " << ofMap(mouseY, 0, ofGetHeight(), -90, 90) << endl;
    cout << "overall_rotation: " << overall_rotation << endl;
    cout << "cam properties" << endl;
    cout << "cam.getGlobalPosition():    " << cam.getGlobalPosition() << endl;
    cout << "cam.getGlobalOrientation(): " << cam.getGlobalOrientation() << endl;
    cout << "cam.getDistance():          " << cam.getDistance() << endl;
    cout << "cam_orientation: " << cam_orientation << endl;
    cout << "cam_position:    " << cam_position << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key){
        // CAMERA MOVEMENTS
        case '[': {
            cam_move_acceleration.z+=cam_move_speed;
            break;
        }
        case ']': {
            cam_move_acceleration.z-=cam_move_speed;
            break;
        }
        // case OF_KEY_UP: {
        //     cam_move_acceleration.y+=cam_move_speed;
        //     break;
        // }
        // case OF_KEY_DOWN: {
        //     cam_move_acceleration.y-=cam_move_speed;
        //     break;
        // }
        // case OF_KEY_RIGHT: {
        //     cam_move_acceleration.x+=cam_move_speed;
        //     break;
        // }
        // case OF_KEY_LEFT: {
        //     cam_move_acceleration.x-=cam_move_speed;
        //     break;
        // }
        //
        case 'q':{
            cam_orient_acceleration.x -= cam_orient_speed;
            break;
        }
        case 'w':{
            cam_orient_acceleration.x += cam_orient_speed;
            break;
        }
        case 'a':{
            cam_orient_acceleration.y -= cam_orient_speed;
            break;
        }
        case 's':{
            cam_orient_acceleration.y += cam_orient_speed;
            break;
        }
        case 'z':{
            cam_orient_acceleration.z -= cam_orient_speed;
            break;
        }
        case 'x':{
            cam_orient_acceleration.z += cam_orient_speed;
            break;
        }
    }

}

//--------------------------------------------------------------
// ARDUINO METHODS
//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

    /* // a little blink to start
    for (int i = 0; i < 5; i++){
	    arduino.sendDigital(13, ARD_LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    arduino.sendDigital(13, ARD_HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    } */
    
    // it is now safe to send commands to the Arduino
    can_setup_arduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << arduino.getFirmwareName(); 
    ofLogNotice() << "firmata v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();

    // set pin 2 as INPUT_PULLUP
    arduino.sendDigitalPinMode(2, ARD_INPUT);
    arduino.sendDigital(2, ARD_HIGH);

    // set pin A0, A1 to analog input
    arduino.sendAnalogPinReporting(0, ARD_ANALOG);
    arduino.sendAnalogPinReporting(1, ARD_ANALOG);
	
    // Listen for changes on the digital and analog pins
    ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);    
}

//--------------------------------------------------------------
void ofApp::updateArduino(){
	arduino.update();
}

//--------------------------------------------------------------
// digital pin event handler, called whenever a digital pin value has changed
//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pinNum) {
    if (pinNum == 2) joystick_pressed = !arduino.getDigital(pinNum);
}

//--------------------------------------------------------------
// analog pin event handler, called whenever an analog pin value has changed
//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    float joystick_speed_divider = 6.5f;
    switch(pinNum){
        case 0:{
            joystick.y = ofMap(arduino.getAnalog(pinNum), 1023, 0, -cam_move_speed/joystick_speed_divider, cam_move_speed/joystick_speed_divider);
            break;
        }
        case 1:{
            joystick.x = ofMap(arduino.getAnalog(pinNum), 1023, 0, -cam_move_speed/joystick_speed_divider, cam_move_speed/joystick_speed_divider);
            break;
        }
    }
    analog_status = "joystick x: " + ofToString(joystick.x) + ", y: " + ofToString(joystick.y);
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