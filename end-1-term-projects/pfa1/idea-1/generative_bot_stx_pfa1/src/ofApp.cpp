#include "ofApp.h"

//--------------------------------------------------------------
// Naming convention is like that:
// camelCase for openframeworks variables, functions and methods
// UpperCamelCase for classes
// UPPERCASE for variables that are defined just once and never modified
// lowercase_like_that for my variables, functions and methods
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);

    // generate a random runtime
    APP_RUNTIME_MS = int(ofRandom(30, 40)) * 60 * 1000; // ms * 1000 = seconds

    // GENERAL GRAPHICS VARIABLES INIT
    save_animation = false;
    dark_mode = true;
    bw_mode = true;
    bg_color = (dark_mode == true) ? 5 : 255;
    starting_hue = (bw_mode == true) ? 0 : 140;
    
    cout << "Starting hue: " << starting_hue << endl;

    // TYPOGRAPHY
    // init fbo for drawing words
    // typography_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 8);
    typography_fbo.allocate(OUTPUT_WIDTH, OUTPUT_HEIGHT, GL_RGBA, 8);

    // vertical sizing of the letters 
    vertical_size = OUTPUT_HEIGHT / 20;

    // main font used for the typography fbo
    current_font = "AvenirNext-Medium-06";
    font.load("fonts/" + ofToString(current_font) + ".ttf", vertical_size, true, true, true);
    
    // parse the json with the words array
    string words_json_path = "words_frequency_score.json";
    
    if (!JSON_words_count_score.open(words_json_path)){
        ofLogNotice() << "Failed to parse input Json File, exiting app." << endl;
        ofExit();
    }

    if (DEBUG_JSON){
        cout << "is JSON file array? ";
        JSON_words_count_score.isArray() == true ? ofLogNotice() << "yes" : ofLogNotice() << "no";
    }

    created_words = generate_typography(JSON_words_count_score, font, vertical_size);
    
    // add listeners to gui parameters
    noise_x_speed_GUI.addListener(this, &ofApp::changed_field_param);
    noise_y_speed_GUI.addListener(this, &ofApp::changed_field_param);
    cell_size_GUI.addListener(this, &ofApp::changed_field_param);
    //render_grid_GUI.addListener(this, &ofApp::changed_bool_param);
    
    // setup gui
    show_gui = false;
    gui.setup();
    gui.add(cell_size_GUI.set("Cell Size", 64.0f, 2.0f, 256.0f));
    gui.add(noise_x_speed_GUI.set("Noise X Offset", 0.1f, 0.00001f, 0.1f));
    gui.add(noise_y_speed_GUI.set("Noise Y Offset", 0.001f, 0.00001f, 0.06f));
    gui.add(alignment_amount_GUI.set("Alignment Amount", 1.0f, 0.0f, 16.0f));
    gui.add(separation_amount_GUI.set("Separation Amount", 1.0f, 0.0f, 8.0f));
    gui.add(separation_threshold_distance_GUI.set("Separation Dist", 5.0f, 0.0f, 10.0f));
    gui.add(field_attraction_GUI.set("Field Attraction", 4.0f, 0.0f, 64.f));
    gui.add(max_force_GUI.set("MAX FORCE", 0.6f, 0.01f, 5.0f));
    gui.add(max_steer_GUI.set("MAX STEER", 0.7f, 0.01f, 5.0f));
    gui.add(max_speed_GUI.set("MAX SPEED", 1.0f, 0.01f, 5.0f));
    gui.add(render_grid_GUI.set("Show Grid", false));
    gui.add(clear_canvas_GUI.set("Clear Canvas", true));
    gui.add(show_fear_text_GUI.set("Show Fear Text", false));
    
    // setup flowfield
    flow_field.initGrid(0.008f, 0.014f, ofVec2f(32.0f, 32.0f));
    
    // choose numbers of boids
    BOIDS_NUM = 6144;
    
    // fill boids vector
    for(int i = 0; i < BOIDS_NUM; i++){
        Boid * newBoid = new Boid();
        // ofVec2f newPos = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        ofVec2f newPos = ofVec2f(ofRandom(0, OUTPUT_WIDTH), ofRandom(0, OUTPUT_HEIGHT));
        newBoid->setup(newPos, ofVec2f(1, 1));
        boids.push_back(newBoid);
    }
    // init and clear boids fbo
    // boids_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB, 4);
    boids_fbo.allocate(OUTPUT_WIDTH, OUTPUT_HEIGHT, GL_RGB, 4);
    boids_fbo.begin();
        ofClear(bg_color);
    boids_fbo.end();
    
    // parse the json with the args
    if(json_arguments.open("args.json")){
        
        // read the cmd args from the json file
        // Set the gui with those args
        update_GUI_with_JSON_args(json_arguments);
        
        if(DEBUG_JSON){
            ofLog(OF_LOG_NOTICE, "args.json : " + json_arguments.getRawString());
            ofLog(OF_LOG_NOTICE, "args size : " + ofToString(json_arguments["args"].size()));
            ofLog(OF_LOG_NOTICE, "args as array elements : ");
            for(int i = 0; i < json_arguments["args"].size(); i++){
                ofLog(OF_LOG_NOTICE, ofToString(json_arguments["args"].operator[](i)));
            }
        }
    }
    else {
        ofLog(OF_LOG_ERROR, "Failed to parse json");
        ofExit();
    }
    
    if(dark_mode){
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    }
    else {
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    }

    ofBackground(bg_color);

    // TYPE
    render_typography(typography_fbo, created_words, font);

    // update pixels
    typography_fbo.getTexture().readToPixels(type_fbo_pixels);
}

//--------------------------------------------------------------
void ofApp::update(){

    // BOIDS
    starting_hue += 0.0005f;
    
    // update static constants for boids
    Boid::max_force = max_force_GUI.get();
    Boid::max_steer = max_steer_GUI.get();
    Boid::max_speed = max_speed_GUI.get();
    
    // pixels from the fear text fbo
    ofPixels fear_words_pixels;
    typography_fbo.getTexture().readToPixels(fear_words_pixels);
    
    // update boids
    for(int i = 0; i < boids.size(); i++){
        
        // the boids have fear of the white pixels in the typography fbo (press f to show it)
        ofColor currentTextFearColor = fear_words_pixels.getColor(boids[i]->getPosition().x, boids[i]->getPosition().y);
        
        if(currentTextFearColor.r < 30){
            // boids[i]->fear(boids[i]->getPosition(), 60);
            boids[i]->fear(boids[i]->getPosition(), 30);
        }
        
        //boids[i]->fear(ofVec2f(ofGetMouseX(), ofGetMouseY()));
        // boids[i]->follow(ofVec2f(ofGetMouseX(), ofGetMouseY()));
        boids[i]->flock(boids, alignment_amount_GUI.get(), separation_amount_GUI.get(), separation_threshold_distance_GUI.get());
        ofVec2f fieldAttraction = flow_field.computeAttraction(boids[i]);
        fieldAttraction.scale(field_attraction_GUI.get());
        //cout << "Field attraction: " << ofToString(fieldAttraction) << endl;
        //cout << "Boid acceleration: " << boids[i]->getAcceleration() << ", velocity:" << boids[i]->getVelocity() << endl;
        boids[i]->addForce(fieldAttraction);
        boids[i]->update(true);
    }
    
    // close app after it has been running for the requested time
    if(ofGetElapsedTimeMillis() >= APP_RUNTIME_MS){
        cout << "closing app" << endl;
        // save_fbo_image("output/screen_" + ofToString(ofGetFrameNum()) + current_font + ".tif");
        save_fbo_image("output/the_final_one.tif");
        save_fbo_image("output/the_final_one.png");
        ofExit();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    starting_hue += 0.002f;

    // BOIDS
    for(int i = 0; i < boids.size(); i++){

        // set color
        ofColor target_color;
        // float max_distance = ofDist(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()*2, ofGetHeight()*2);
        // float mapped_color = ofMap(ofDist(boids[i]->getPosition().x,
        //                                 boids[i]->getPosition().y,
        //                                 ofGetWidth()/2,
        //                                 ofGetHeight()/2),
        //                                 0, max_distance, 30, 0);

        // float boid_dist_from_center = ofDist(boids[i]->getPosition().x, boids[i]->getPosition().y, ofGetWidth(), ofGetHeight());
        // float mapped_color = ofMap(boid_dist_from_center, 0, max_distance, 255, 80);

        float saturation;
        if (bw_mode){
            saturation = ofMap(ofNoise(boids[i]->getPosition().x, boids[i]->getPosition().y), 0, 1, 0, 5);
        }
        else {
            saturation = ofMap(ofNoise(boids[i]->getPosition().x, boids[i]->getPosition().y), 0, 1, 0, 255);
        }
        
        if (dark_mode){
            target_color.setHsb(starting_hue, saturation, 100, 8);
        }
        else {
            target_color.setHsb(starting_hue, saturation, 17, 5);
        }
        
        // ofColor current_color = type_fbo_pixels.getColor(boids[i]->getPosition().x, boids[i]->getPosition().y);
        boids[i]->render(target_color, &boids_fbo);
    }

    if(clear_canvas_GUI.get()){
        boids_fbo.begin();
        ofClear(bg_color, 255);
        boids_fbo.end();
    }
    
    clear_canvas_GUI.set(false);
    
    // render grid
    if(render_grid_GUI.get()){
        flow_field.drawGrid();
    }
    
    // visualize fear text
    if(show_fear_text_GUI){
        typography_fbo.draw(0, 0);
    }

    // boids
    boids_fbo.draw(0, 0);
    
    // gui
    if (show_gui){
        gui.draw();
    }

    // animation
    if (save_animation){
        string filename = "output/animation/screen_anim_" + ofToString(ofGetFrameNum()) + ".jpg";
        ofSaveScreen(filename);
    }
    
    // DEBUG
    // ofDrawBitmapString("Starting hue: " + ofToString(starting_hue), ofGetWidth()-200, 20);
}

//--------------------------------------------------------------
void ofApp::changed_field_param(float & value){
    // Update grid
    if(cell_size_GUI.get() != 0) flow_field.initGrid(noise_x_speed_GUI.get(), noise_y_speed_GUI.get(), ofVec2f(cell_size_GUI.get(), cell_size_GUI.get()));
}
//--------------------------------------------------------------
void ofApp::changed_bool_param(bool &value){
    // Update grid
    
}

//--------------------------------------------------------------
void ofApp::update_GUI_with_JSON_args(ofxJSONElement jsonFile){
    
    if (DEBUG_JSON) ofLog(OF_LOG_NOTICE, "Reading GUI parameters from args.json");
    
    float currentValue = 0.0f;
    for(int i = 0; i < json_arguments["args"].size(); i++){
        currentValue = json_arguments["args"].operator[](i).asFloat();
        //if(DEBUG_JSON) ofLog(OF_LOG_NOTICE, ofToString(currentValue) +"\n");
        // Set GUI parameters based on index of appearance
        string logString;
        switch (i) {
            case 0:
                max_force_GUI.set(currentValue);
                break;
            case 1:
                max_speed_GUI.set(currentValue);
                break;
            case 2:
                max_steer_GUI.set(currentValue);
                break;
            case 3:
                alignment_amount_GUI.set(currentValue);
                break;
            case 4:
                field_attraction_GUI.set(currentValue);
                break;
            case 5:
                separation_amount_GUI.set(currentValue);
                break;
            case 6:
                separation_threshold_distance_GUI.set(currentValue);
                break;
            case 7:
                noise_x_speed_GUI.set(currentValue);
                break;
            case 8:
                noise_y_speed_GUI.set(currentValue);
                break;
            case 9:
                cell_size_GUI.set(currentValue);
                break;\
                
            default:
                break;
        }
    }
    
    if (DEBUG_JSON) ofLog(OF_LOG_NOTICE, "Done!");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // Save settings to xml file
    switch(key){
        // show gui
        case 'i':{
            show_gui = !show_gui;
            break;
        }
        case 'f':{
            show_fear_text_GUI == true ? show_fear_text_GUI.set(false) : show_fear_text_GUI.set(true);
            break;
        }
        // save settings
        case 's':{
            // Clear old file
            xml_settings.clear();
            if(xml_settings.saveFile("settings.xml")){
                cout << "Saving settings.xml.." << endl;
                
                xml_settings.addTag("settings");
                xml_settings.pushTag("settings");
                // Save general settings
                xml_settings.addValue("max_force", max_force_GUI.get());
                xml_settings.addValue("max_speed", max_speed_GUI.get());
                xml_settings.addValue("max_steer", max_steer_GUI.get());
                xml_settings.addValue("flock_align", alignment_amount_GUI.get());
                xml_settings.addValue("field_attraction", field_attraction_GUI.get());
                xml_settings.addValue("separation_amount", separation_amount_GUI.get());
                xml_settings.addValue("separation_threshold", separation_threshold_distance_GUI.get());
                // Save noise settings
                xml_settings.addTag("noise_speed");
                xml_settings.pushTag("noise_speed");
                xml_settings.addValue("X", noise_x_speed_GUI.get());
                xml_settings.addValue("Y", noise_y_speed_GUI.get());
                xml_settings.popTag();
                // Save cell size
                xml_settings.addTag("cell_size");
                xml_settings.pushTag("cell_size");
                xml_settings.addValue("X", cell_size_GUI.get());
                xml_settings.addValue("Y", cell_size_GUI.get());
                xml_settings.popTag();
                xml_settings.popTag();
                xml_settings.saveFile("settings.xml");
                cout << "Saved!" << endl;
            }
            break;
        }
        // load previous settings
        case 'r':{
            if(xml_settings.loadFile("settings.xml")){
                cout << "Reading previous settings.xml.." << endl;
                xml_settings.pushTag("settings");
                max_force_GUI.set(xml_settings.getValue("max_force", 0.0f));
                max_speed_GUI.set(xml_settings.getValue("max_speed", 0.0f));
                max_steer_GUI.set(xml_settings.getValue("max_steer", 0.0f));
                alignment_amount_GUI.set(xml_settings.getValue("flock_align", 0.0f));
                field_attraction_GUI.set(xml_settings.getValue("field_attraction", 0.0f));
                separation_amount_GUI.set(xml_settings.getValue("separation_amount", 0.0f));
                separation_threshold_distance_GUI.set(xml_settings.getValue("separation_threshold", 0.0f));
                xml_settings.pushTag("noise_speed");
                noise_x_speed_GUI.set(xml_settings.getValue("X", 0.008f));
                noise_y_speed_GUI.set(xml_settings.getValue("Y", 0.014f));
                xml_settings.popTag();
                xml_settings.pushTag("cell_size");
                cell_size_GUI.set(xml_settings.getValue("X", 64.0f));
                xml_settings.popTag();
                xml_settings.popTag();
            }
            else {
                ofLog(OF_LOG_ERROR, "settings.xml does not exist");
            }
            break;
        }
        // save image
        case 'w':{
            save_fbo_image("output/screen_" + ofToString(ofGetFrameNum()) + current_font + ".tif");
            break;
        }
        // save fear text as image
        case 't':{
            ofPixels pixels;
            typography_fbo.getTexture().readToPixels(pixels);
            ofSaveImage(pixels, "fear_text.png");
            break;
        }
    }
}

//--------------------------------------------------------------
// get fbo boids pixels and save image to given path
//--------------------------------------------------------------
void ofApp::save_fbo_image(string path){

    string image_name = ofToString(path);
    ofPixels pixels;
    ofImage out_image;
    boids_fbo.getTexture().readToPixels(pixels);
    out_image.setFromPixels(pixels);
    out_image.save(image_name);
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    noise_x_speed_GUI.removeListener(this, &ofApp::changed_field_param);
    noise_y_speed_GUI.removeListener(this, &ofApp::changed_field_param);
    cell_size_GUI.removeListener(this, &ofApp::changed_field_param);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
