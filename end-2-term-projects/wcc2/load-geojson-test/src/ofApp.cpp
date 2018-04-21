#include "ofApp.h"
#include <algorithm>

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
	ofSetFrameRate(60);

    ofHideCursor();

    // FBO FOR THE 3D ENVIRONMENT 
    threed_map_fbo.allocate(WIDTH/2, HEIGHT, GL_RGBA, 8);
    // CANVAS FOR THE GENERATIVE ARTWORK
    sand_line.setup(WIDTH/2, HEIGHT, 1, 35);
    draw_artwork = false;

    // TYPE
    font.load("fonts/AndaleMono.ttf", 15, true, true, true, 1.0f);
    legend_font.load("fonts/AndaleMono.ttf", 8, true, true, true, 1.0f);

    // ARDUINO
    joystick_pressed = false;
    arduino.connect("/dev/tty.usbmodem11", 57600);
    can_setup_arduino = false;
    joystick = ofVec2f(0, 0);

    // listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setup_arduino()
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	can_setup_arduino = false;

    // OSC
    current_tweeted_city = "";
    current_tweet_hashtags = "";
    osc_receiver.setup(9000);

    // 3D
    text_scale = 0.2f;
    // fireworks
    // firework.setup(ofVec3f(0,0,0), ofFloatColor(1.0, 0, 0));
    // don't use the normal gl texture
	ofDisableArbTex();
    ofLoadImage(firework_texture, "solid_dot.png");
    glPointSize(8);
    fireworks_colors.push_back(ofFloatColor(1, 0, 0.780));
    fireworks_colors.push_back(ofFloatColor(1, 0, 0.094));
    fireworks_colors.push_back(ofFloatColor(0.282, 1, 0));
    fireworks_colors.push_back(ofFloatColor(1, 0.494, 0));
    fireworks_colors.push_back(ofFloatColor(0, 0.188, 1));
    fireworks_colors.push_back(ofFloatColor(1, 0.968, 0));
    fireworks_colors.push_back(ofFloatColor(0, 0.925, 1));

    // CAMERA
    // cam.setDistance(610);
    cam.setNearClip(0.5);
    // cam.setFarClip(1200);
    // camera movement and orientation settings
    // cam_move_speed = 1.265f;
    cam_move_speed = 0.065f;
    cam_position = ofPoint(0, -212, 512);
    cam_move_velocity = ofVec3f(0, 0, 0);
    cam_move_acceleration = ofVec3f(0, 0, 0);
    // orientation
    cam_orient_speed = 0.05f;
    cam_orientation = ofVec3f(26, 0, 0);
    cam_orient_velocity = ofVec3f(0, 0, 0);
    cam_orient_acceleration = ofVec3f(0, 0, 0);

    // SOUND
    // chatting_sound_en.load("sounds/fill.wav");
    // chatting_sound_jp.load("sounds/hihat_1.wav");
    // chatting_sound_es.load("sounds/synth.wav");
    // chatting_sound_fr.load("sounds/kick_1.wav");
    chatting_sound_en.load("sounds/chatting_en.wav");
    chatting_sound_jp.load("sounds/chatting_jp.wav");
    chatting_sound_es.load("sounds/chatting_es.wav");
    chatting_sound_fr.load("sounds/chatting_fr.wav");
    chatting_sound_it.load("sounds/chatting_it.wav");
    // sound_else.load("sounds/kick_1.wav");
    
    chatting_sound_en.setVolume(0.5f);
    // chatting_sound_en.setMultiPlay(true);
    chatting_sound_jp.setVolume(0.5f);
    // chatting_sound_jp.setMultiPlay(true);
    chatting_sound_es.setVolume(0.5f);
    // chatting_sound_es.setMultiPlay(true);
    chatting_sound_fr.setVolume(0.5f);
    chatting_sound_it.setVolume(0.5f);
    sound_else.setVolume(0.25f);
    // chatting_sound_fr.setMultiPlay(true);

    // GEOJSON
    geojson_scale = 400;
    std::string file_path = "world_cities_countries.geojson";
    // geoshape_bb = ofRectangle(ofPoint(-120, -36), 170, 80); // testing on the macbook air
    geoshape_bb = ofRectangle(ofPoint(-310, -120), 406, 184); // with the full res

    // create the actual geojson meshes and return the centroid
    ofPoint geoshape_centroid = vv_geojson::create_geojson_map(file_path, font, poly_meshes, cities, geojson_scale);
    
    // let the cam look at the centroid of the shape
    cam.lookAt(geoshape_centroid);

    // clean the buffer
    threed_map_fbo.begin();
    ofClear(255);
    threed_map_fbo.end();

    cout << "overall centroid: " << geoshape_centroid << endl;
    cout << "ended parsing of file" << endl;
    cout << "poly_meshes.size(): " << poly_meshes.size() << endl;
    cout << "cities.size(): " << cities.size() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

    // update the artwork
    sand_line.update();

    // update the dataviz
    for (int f = 0; f < fireworks.size(); f++){
        fireworks.at(f).update();
    }

    updateArduino();
    // move and orient camera
    compute_cam_movement();
    compute_cam_orientation();

    // check for osc messages
	while(osc_receiver.hasWaitingMessages()){
        ofxOscMessage m;
        osc_receiver.getNextMessage(m);

        if(m.getAddress() == "/twitter-app"){

			current_tweeted_city = "#" + m.getArgAsString(0);
            // if there's no text, we'll have an empty string, otherwise prepend an hashtag
			current_tweet_hashtags = m.getArgAsString(1).length() == 0 ? "" : "#" + m.getArgAsString(1);
			std::string current_tweet_nation = m.getArgAsString(2);
			float lon = m.getArgAsFloat(3);
			float lat = m.getArgAsFloat(4);

            // cout << "heard a tweet related to: " << current_tweeted_city;
            // cout << ", nation: " << current_tweet_nation;
            // cout << ", coordinates: " << lon << ", " << lat << endl;

            ofVec3f city_pos;
            bool found = false;

            // if the tweet has the coordinates embedded, use them
            if (lon != -1 && lat != -1){
                city_pos = vv_map_projections::mercator(lon, lat, geojson_scale);
                found = true;
            }
            // otherwise we will find them by ourselves
            else {
                for (int i = 0; i < cities.size(); i++){
                    
                    if (cities.at(i).name == current_tweeted_city){
                        city_pos = cities.at(i).position;
                        found = true;
                    }

                    if (found) break;
                }
            }

            if (found){
                if (fireworks.size() > 15){
                    fireworks.pop_front();
                }
                // VISUALIZATION
                // add a firework to visualize the tweet
                Firework firework;
                // ofFloatColor col = fireworks_colors.at(ofRandom(fireworks_colors.size()));
                ofFloatColor col = ofFloatColor(0.0f);
                firework.setup(city_pos, col);
                fireworks.push_back(firework);

                // SOUND
                play_sound_for_nation(current_tweet_nation);

                // DRAWING
                // use that city in the artwork
                ofPoint screen_pos;
                ofFbo * fbo = sand_line.get_fbo_pointer();
                screen_pos.x = ofMap(city_pos.x, geoshape_bb.x, geoshape_bb.getWidth(),  0, fbo->getWidth());
                screen_pos.y = ofMap(city_pos.y, geoshape_bb.y, geoshape_bb.getHeight(), fbo->getHeight(), 0);
                // get the max offset from the second letter of the tweet (first char is the hashtag)
                int max_offset;
                try {
                    max_offset = int(current_tweet_hashtags.at(1)) * 0.5f;
                }
                catch (std::out_of_range &exc){
                    max_offset = ofRandom(255);
                }
                // get the max radius from the length of the tweet
                int max_radius = ofClamp(int(current_tweet_hashtags.length()), 32, 64);
                // cout << "adding line with max offset: " << max_offset << endl;

                // pick a random drawing bode, for the moment
                int drawing_mode = (ofRandom(1) > 0.75 ? SandLine::ATTRACTOR_MODE : SandLine::BEZIER_MODE);
                sand_line.set_mode(drawing_mode);
                sand_line.set_target(screen_pos);
                sand_line.add_point(screen_pos, max_offset, max_radius);
            }
            else {
                cerr << "!!!!!!ATTENTION!!!!!!" << endl;
                cerr << "city " << current_tweeted_city << " not found!" << endl;
            }
		}
    }

    // update the sound playing system
	ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw(){

    threed_map_fbo.begin();

    ofPushStyle();
    
    ofBackground(255);
    ofSetColor(0);
    ofFill();

    // 3D STUFF

    ofEnableDepthTest();

    cam.setPosition(cam_position); // see compute_cam_movement()
    cam.setOrientation(cam_orientation);

    cam.begin();

    // ofDrawAxis(320); // for debugging
    
    // move shape to the center of the world
    ofTranslate(-geoshape_centroid);

    // for debugging
    // ofSetColor(255, 0, 0);
    // ofDrawSphere(geoshape_bb.x, geoshape_bb.y, 0, 8);
    // ofDrawSphere(geoshape_bb.getWidth(), geoshape_bb.getHeight(), 0, 8);

    // draw the vbo meshes for the polygons
    ofSetColor(255, 0, 0);
    for (int i = 0; i < poly_meshes.size(); i++){
        poly_meshes.at(i).draw();
    }

    // draw the text of each city
    for (int i = 0; i < cities.size(); i++){
        ofPushMatrix();

            ofPoint city_screen_pos = cam.worldToScreen(cities.at(i).position);
            // check if the city can actually be seen from the camera
            // otherwise don't even bother doing all this stuff (this saves a good 20-30fps)
            if (city_screen_pos.x > 0 && city_screen_pos.x < WIDTH/2){
                if (city_screen_pos.y > 0 && city_screen_pos.y < HEIGHT){
            
                    ofTranslate(cities.at(i).position);
                    ofTranslate(0, 0, -0.1f);
                    ofRotateX(-90);
                    // ofScale(0.02, 0.02, 0.02);
                    for (int m = 0; m < cities.at(i).meshes.size(); m++){
                        cities.at(i).meshes.at(m).draw();
                    }
                }
            } 
        ofPopMatrix();
    }

    // fireworks
    // ofEnableAlphaBlending();
    // ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    ofEnablePointSprites();
    ofSetColor(255);

    for (int f = 0; f < fireworks.size(); f++){
        
        Firework * firework = &fireworks.at(f);

        if (!firework->exploded()){
            ofDrawSphere(
                firework->initial_particle.position.x,
                firework->initial_particle.position.y,
                firework->initial_particle.position.z,
                0.23);
        }
        else {
            // all points drawed after the bind will be displayed
            // as the texture instead
            firework_texture.bind();
            firework->mesh.draw();
            firework_texture.unbind();
        }
    }

    // ofDisableAlphaBlending();
    // ofDisableBlendMode();
    ofDisablePointSprites();

    cam.end();
    // key_light_1.disable();

    ofPopStyle();

    ofDisableDepthTest();

    // 2D STUFF

    // DATA 
    ofPushStyle();

    ofSetColor(0);
    ofFill();
    // ofDrawBitmapString(current_tweeted_city, 20, 30);
    font.drawString(current_tweeted_city, 20, 30);
    font.drawString(current_tweet_hashtags, WIDTH/5, 30);
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 20, 50);
    ofDrawBitmapString("mouse screen coords to world: " + ofToString(cam.screenToWorld(ofPoint(mouseX, mouseY))), 20, 90);
    if (!can_setup_arduino){
        ofDrawBitmapString("arduino not ready...\n", 20, 70);
    }
    else {
        if (joystick_pressed) ofDrawBitmapString("joystick pressed!", 20, 70);
        // ofDrawBitmapString(analog_status, 20, 90);
    }
    ofPopStyle();

    threed_map_fbo.end();

    // ARTWORK        
    ofFbo * art_fbo = sand_line.get_fbo_pointer();
    art_fbo->draw(WIDTH/2, 0);

    // DRAW THE 3D ENVIRONMENT
    threed_map_fbo.draw(0, 0);
}


//--------------------------------------------------------------
// CAMERA
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
void ofApp::cam_zoom_in(){
    cam_move_acceleration.z += cam_move_speed;
}

//--------------------------------------------------------------
void ofApp::cam_zoom_out(){
    cam_move_acceleration.z -= cam_move_speed;
}


//--------------------------------------------------------------
// SOUND
//--------------------------------------------------------------
void ofApp::play_sound_for_nation(std::string nation){
    
    // FIXME: play different sounds based on continent
    bool is_orient = (nation == "Japan" || nation == "China");
    bool is_french = (nation == "France");
    bool is_english = (
        nation == "United Kingdom" || 
        nation == "United States" ||
        nation == "Canada" ||
        nation == "Ireland"
    );
    bool is_spanish = (nation == "Kingdom of Spain" || 
        nation == "Portugal" ||
        nation == "Nicaragua" ||
        nation == "Ecuador" ||
        nation == "Andorra"
    );
    bool is_italian = (nation == "Italy");

    float speed = ofRandom(0.85, 1.1);
    if (is_orient){
        // cout << "is orient" << endl;
        // chatting_sound_jp.stop();
        chatting_sound_jp.stop();
        // chatting_sound_jp.setSpeed(speed);
        // chatting_sound_jp.setPositionMS(ofRandom(32 * 1000));
        chatting_sound_jp.play();
    }
    else if (is_english){
        // cout << "is english" << endl;
        // chatting_sound_en.stop();
        chatting_sound_en.stop();
        chatting_sound_en.setSpeed(speed);
        chatting_sound_es.setPositionMS(ofRandom(120 * 1000));
        chatting_sound_en.play();
    }
    else if (is_spanish) {
        // cout << "is spanish" << endl;
        // chatting_sound_es.stop();
        chatting_sound_es.stop();
        chatting_sound_es.setSpeed(speed);
        chatting_sound_es.setPositionMS(ofRandom(60 * 1000));
        chatting_sound_es.play();
    }
    else if (is_french) {
        // cout << "is french" << endl;
        chatting_sound_fr.stop();
        chatting_sound_fr.setSpeed(speed);
        chatting_sound_fr.play();
    }
    else if (is_italian){
        chatting_sound_it.stop();
        chatting_sound_it.setSpeed(speed);
        chatting_sound_it.setPositionMS(ofRandom(35 * 1000));
        chatting_sound_it.play();
    }
    else {
        // TODO:
        // sound_else.stop();
        // sound_else.setSpeed(speed);
        // sound_else.play();
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    cout << "x, y: " << x << ", "  << y << endl;
    cout << "ofMap(mouseX, 0, WIDTH, -90, 90): " << ofMap(mouseX, 0, WIDTH, -90, 90) << endl;
    cout << "ofMap(mouseY, 0, HEIGHT, -90, 90): " << ofMap(mouseY, 0, HEIGHT, -90, 90) << endl;
    cout << "cam properties" << endl;
    cout << "cam.screenToWorld(ofPoint(mouseX, mouseY): " << cam.screenToWorld(ofPoint(mouseX, mouseY)) << endl;
    cout << "cam.getGlobalPosition():    " << cam.getGlobalPosition() << endl;
    cout << "cam.getGlobalOrientation(): " << cam.getGlobalOrientation() << endl;
    cout << "cam.getDistance():          " << cam.getDistance() << endl;
    cout << "cam_orientation: " << cam_orientation << endl;
    cout << "cam_position:    " << cam_position << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // FOR DEBUGGING when the arduino is not plugged
    switch (key){
        // CAMERA MOVEMENTS
        case '[': {
            cam_zoom_in();
            break;
        }
        case ']': {
            cam_zoom_out();
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
    }

}

//--------------------------------------------------------------
// ARDUINO METHODS
//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
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
    
    if (joystick_pressed){
        draw_artwork = true;
    }
}

//--------------------------------------------------------------
// analog pin event handler, called whenever an analog pin value has changed
// it is used here to get the joystick movement on x and y axis
//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    
    // float joystick_speed_divider = 6.5f;
    float joystick_speed_mult = 0.1538f;
    switch(pinNum){
        case 0:{
            joystick.y = ofMap(
                arduino.getAnalog(pinNum),
                1023, 0,
                -cam_move_speed * joystick_speed_mult, cam_move_speed * joystick_speed_mult
            );
            break;
        }
        case 1:{
            joystick.x = ofMap(
                arduino.getAnalog(pinNum),
                1023, 0,
                -cam_move_speed * joystick_speed_mult, cam_move_speed * joystick_speed_mult
            );
            break;
        }
    }
    analog_status = "joystick x: " + ofToString(joystick.x) + ", y: " + ofToString(joystick.y);
}

//--------------------------------------------------------------
void ofApp::save_fbo(ofFbo * fbo, std::string path){

    ofPixels pixels;
    ofImage out_image;
    fbo->getTexture().readToPixels(pixels);
    out_image.setFromPixels(pixels);
    out_image.save(path);
}

//--------------------------------------------------------------
// used to save the image with the current time
// grabbed from https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
//--------------------------------------------------------------
std::string ofApp::current_date_time() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    // strftime(buf, sizeof(buf), "%Y-%m-%d-%H:%M:%S", &tstruct);
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);

    return buf;
}

//--------------------------------------------------------------
void ofApp::exit(){

    ofFbo * fbo = sand_line.get_fbo_pointer();
    
    fbo->begin();

    // add the names of the cities on the fbo
    ofSetColor(255, 65);
    for (int i = 0; i < cities.size(); i++){

        ofPoint screen_pos;
        screen_pos.x = ofMap(cities.at(i).position.x, geoshape_bb.x, geoshape_bb.getWidth(),  0, fbo->getWidth());
        screen_pos.y = ofMap(cities.at(i).position.y, geoshape_bb.y, geoshape_bb.getHeight(), fbo->getHeight(), 0);
        legend_font.drawString(cities.at(i).name, screen_pos.x, screen_pos.y);
    }
    fbo->end();

    cout << "saving fbo...";
    // save_fbo(fbo, current_date_time() + ".png");
    save_fbo(fbo, "test.png");
    // cout << "saving map legend...";
    // save_fbo(fbo, "legend.png");

    cout << " done, exiting" << endl;
}
