#include "ofApp.h"
#include "Type.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);

    // Generate a random runtime
    APP_RUNTIME_MS = int(ofRandom(15, 2)) * 60 * 1000; // ms * 1000 = seconds

    // GENERAL GRAPHICS VARIABLES INIT
    dark_mode = true;
    bg_color = (dark_mode == true) ? 10 : 255;
    starting_hue = (bw_mode == true) ? 0 : ofRandom(255);
    // starting_hue = (bw_mode == true) ? 0 : 170.593;
    
    cout << "Starting hue: " << starting_hue << endl;

    // TYPOGRAPHY
    // init fbo for drawing words
    typography_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 8);
    // vertical sizing of the letters 
    vertical_size = ofGetHeight() / 24;

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

    created_words = generateTypography(JSON_words_count_score, font, vertical_size);
    
    // add listeners to gui parameters
    noiseXSpeedGUI.addListener(this, &ofApp::changedFieldParams);
    noiseYSpeedGUI.addListener(this, &ofApp::changedFieldParams);
    cellSizeGUI.addListener(this, &ofApp::changedFieldParams);
    //shouldRenderGridGUI.addListener(this, &ofApp::changedBoolParam);
    
    // setup gui
    show_gui = true;
    gui.setup();
    gui.add(cellSizeGUI.set("Cell Size", 64.0f, 2.0f, 256.0f));
    gui.add(noiseXSpeedGUI.set("Noise X Offset", 0.1f, 0.00001f, 0.1f));
    gui.add(noiseYSpeedGUI.set("Noise Y Offset", 0.001f, 0.00001f, 0.06f));
    gui.add(alignmentAmountGUI.set("Alignment Amount", 1.0f, 0.0f, 16.0f));
    gui.add(separationAmountGUI.set("Separation Amount", 1.0f, 0.0f, 8.0f));
    gui.add(separationThresholdDistanceGUI.set("Separation Dist", 5.0f, 0.0f, 10.0f));
    gui.add(fieldAttractionGUI.set("Field Attraction", 4.0f, 0.0f, 64.f));
    gui.add(maxForceGUI.set("MAX FORCE", 0.6f, 0.01f, 5.0f));
    gui.add(maxSteerGUI.set("MAX STEER", 0.7f, 0.01f, 5.0f));
    gui.add(maxSpeedGUI.set("MAX SPEED", 1.0f, 0.01f, 5.0f));
    gui.add(shouldRenderGridGUI.set("Show Grid", false));
    gui.add(shouldClearCanvasGUI.set("Clear Canvas", true));
    // gui.add(shouldRenderFearAreasGUI.set("Show Fear Areas", false));
    gui.add(shouldShowFearTextGUI.set("Show Fear Text", false));
    
    // setup flowfield
    flowField.initGrid(0.008f, 0.014f, ofVec2f(32.0f, 32.0f));
    
    // choose numbers of boids
    BOIDS_NUM = 1024;
    
    // fill boids vector
    for(int i = 0; i < BOIDS_NUM; i++){
        Boid * newBoid = new Boid();
        ofVec2f newPos = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        newBoid->setup(newPos, ofVec2f(1, 1));
        boids.push_back(newBoid);
    }
    // init and clear boids fbo
    boids_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB, 4);
    boids_fbo.begin();
        ofClear(bg_color);
    boids_fbo.end();
    
    // parse the json with the args
    if(jsonArguments.open("args.json")){
        
        // read the cmd args from the json file
        // Set the gui with those args
        update_GUI_with_JSON_args(jsonArguments);
        
        if(DEBUG_JSON){
            ofLog(OF_LOG_NOTICE, "args.json : " + jsonArguments.getRawString());
            ofLog(OF_LOG_NOTICE, "args size : " + ofToString(jsonArguments["args"].size()));
            ofLog(OF_LOG_NOTICE, "args as array elements : ");
            for(int i = 0; i < jsonArguments["args"].size(); i++){
                ofLog(OF_LOG_NOTICE, ofToString(jsonArguments["args"].operator[](i)));
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
    renderTypography(typography_fbo, created_words, font);

    // update pixels
    typography_fbo.getTexture().readToPixels(type_fbo_pixels);
}

//--------------------------------------------------------------
void ofApp::update(){

    // BOIDS
    starting_hue += 0.001f;
    
    // update static constants for boids
    Boid::max_force = maxForceGUI.get();
    Boid::max_steer = maxSteerGUI.get();
    Boid::max_speed = maxSpeedGUI.get();
    
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
        boids[i]->flock(boids, alignmentAmountGUI.get(), separationAmountGUI.get(), separationThresholdDistanceGUI.get());
        ofVec2f fieldAttraction = flowField.computeAttraction(boids[i]);
        fieldAttraction.scale(fieldAttractionGUI.get());
        //cout << "Field attraction: " << ofToString(fieldAttraction) << endl;
        //cout << "Boid acceleration: " << boids[i]->getAcceleration() << ", velocity:" << boids[i]->getVelocity() << endl;
        boids[i]->addForce(fieldAttraction);
        boids[i]->update(true);
    }
    
    // close app after it has been running for the requested time
    if(ofGetElapsedTimeMillis() >= APP_RUNTIME_MS){
        cout << "closing app" << endl;
        saveFBOImage("output/screen_" + ofToString(ofGetFrameNum()) + current_font + ".jpg");
        ofExit();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    starting_hue += 0.005f;

    // BOIDS
    for(int i = 0; i < boids.size(); i++){

        // set color
        ofColor target_color;
        float max_distance = ofDist(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()*2, ofGetHeight()*2);
        // float mapped_color = ofMap(ofDist(boids[i]->getPosition().x,
        //                                 boids[i]->getPosition().y,
        //                                 ofGetWidth()/2,
        //                                 ofGetHeight()/2),
        //                                 0, max_distance, 30, 0);

        // float boid_dist_from_center = ofDist(boids[i]->getPosition().x, boids[i]->getPosition().y, ofGetWidth(), ofGetHeight());
        // float mapped_color = ofMap(boid_dist_from_center, 0, max_distance, 255, 80);

        float saturation = ofMap(ofNoise(boids[i]->getPosition().x, boids[i]->getPosition().y), 0, 1, 0, 255);
        
        // B & W
        if (dark_mode){
            target_color.setHsb(starting_hue, saturation, 200, 5);
        }
        else {
            target_color.setHsb(starting_hue, saturation, 17, 10);
        }
        
        // ofColor current_color = type_fbo_pixels.getColor(boids[i]->getPosition().x, boids[i]->getPosition().y);
        boids[i]->render(target_color, &boids_fbo);
        
        // if (current_color.r > 250){
        //     boids[i]->render(ofColor(0), &boids_fbo);
        // }
        // else {
        //     boids[i]->render(ofColor(255), &boids_fbo);
        // }
    }

    if(shouldClearCanvasGUI.get()){
        boids_fbo.begin();
        ofClear(bg_color, 255);
        boids_fbo.end();
    }
    
    shouldClearCanvasGUI.set(false);
    
    // render grid
    if(shouldRenderGridGUI.get()){
        flowField.drawGrid();
    }
    
    // visualize fear text
    if(shouldShowFearTextGUI){
        typography_fbo.draw(0, 0);
    }
    
    // visualize fear areas
    // if(shouldRenderFearAreasGUI){
    //     for(int fa = 0; fa < fearAreas.size(); fa++){
    //         fearAreas[fa]->render();
    //     }
    // }

    // boids
    boids_fbo.draw(0, 0);
    
    // gui
    if (show_gui){
        gui.draw();
    }
    
    // DEBUG
    // ofDrawBitmapString("Starting hue: " + ofToString(starting_hue), ofGetWidth()-200, 20);
}

//--------------------------------------------------------------
void ofApp::changedFieldParams(float & value){
    // Update grid
    if(cellSizeGUI.get() != 0) flowField.initGrid(noiseXSpeedGUI.get(), noiseYSpeedGUI.get(), ofVec2f(cellSizeGUI.get(), cellSizeGUI.get()));
}
//--------------------------------------------------------------
void ofApp::changedBoolParam(bool &value){
    // Update grid
    
}

//--------------------------------------------------------------
void ofApp::update_GUI_with_JSON_args(ofxJSONElement jsonFile){
    
    if (DEBUG_JSON) ofLog(OF_LOG_NOTICE, "Reading GUI parameters from args.json");
    
    float currentValue = 0.0f;
    for(int i = 0; i < jsonArguments["args"].size(); i++){
        currentValue = jsonArguments["args"].operator[](i).asFloat();
        //if(DEBUG_JSON) ofLog(OF_LOG_NOTICE, ofToString(currentValue) +"\n");
        // Set GUI parameters based on index of appearance
        string logString;
        switch (i) {
            case 0:
                maxForceGUI.set(currentValue);
                break;
            case 1:
                maxSpeedGUI.set(currentValue);
                break;
            case 2:
                maxSteerGUI.set(currentValue);
                break;
            case 3:
                alignmentAmountGUI.set(currentValue);
                break;
            case 4:
                fieldAttractionGUI.set(currentValue);
                break;
            case 5:
                separationAmountGUI.set(currentValue);
                break;
            case 6:
                separationThresholdDistanceGUI.set(currentValue);
                break;
            case 7:
                noiseXSpeedGUI.set(currentValue);
                break;
            case 8:
                noiseYSpeedGUI.set(currentValue);
                break;
            case 9:
                cellSizeGUI.set(currentValue);
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
            shouldShowFearTextGUI == true ? shouldShowFearTextGUI.set(false) : shouldShowFearTextGUI.set(true);
            break;
        }
        // save settings
        case 's':{
            // Clear old file
            xmlSettings.clear();
            if(xmlSettings.saveFile("settings.xml")){
                cout << "Saving settings.xml.." << endl;
                
                xmlSettings.addTag("settings");
                xmlSettings.pushTag("settings");
                // Save general settings
                xmlSettings.addValue("max_force", maxForceGUI.get());
                xmlSettings.addValue("max_speed", maxSpeedGUI.get());
                xmlSettings.addValue("max_steer", maxSteerGUI.get());
                xmlSettings.addValue("flock_align", alignmentAmountGUI.get());
                xmlSettings.addValue("field_attraction", fieldAttractionGUI.get());
                xmlSettings.addValue("separation_amount", separationAmountGUI.get());
                xmlSettings.addValue("separation_threshold", separationThresholdDistanceGUI.get());
                // Save noise settings
                xmlSettings.addTag("noise_speed");
                xmlSettings.pushTag("noise_speed");
                xmlSettings.addValue("X", noiseXSpeedGUI.get());
                xmlSettings.addValue("Y", noiseYSpeedGUI.get());
                xmlSettings.popTag();
                // Save cell size
                xmlSettings.addTag("cell_size");
                xmlSettings.pushTag("cell_size");
                xmlSettings.addValue("X", cellSizeGUI.get());
                xmlSettings.addValue("Y", cellSizeGUI.get());
                xmlSettings.popTag();
                xmlSettings.popTag();
                xmlSettings.saveFile("settings.xml");
                cout << "Saved!" << endl;
            }
            break;
        }
        // load previous settings
        case 'r':{
            if(xmlSettings.loadFile("settings.xml")){
                cout << "Reading previous settings.xml.." << endl;
                xmlSettings.pushTag("settings");
                maxForceGUI.set(xmlSettings.getValue("max_force", 0.0f));
                maxSpeedGUI.set(xmlSettings.getValue("max_speed", 0.0f));
                maxSteerGUI.set(xmlSettings.getValue("max_steer", 0.0f));
                alignmentAmountGUI.set(xmlSettings.getValue("flock_align", 0.0f));
                fieldAttractionGUI.set(xmlSettings.getValue("field_attraction", 0.0f));
                separationAmountGUI.set(xmlSettings.getValue("separation_amount", 0.0f));
                separationThresholdDistanceGUI.set(xmlSettings.getValue("separation_threshold", 0.0f));
                xmlSettings.pushTag("noise_speed");
                noiseXSpeedGUI.set(xmlSettings.getValue("X", 0.008f));
                noiseYSpeedGUI.set(xmlSettings.getValue("Y", 0.014f));
                xmlSettings.popTag();
                xmlSettings.pushTag("cell_size");
                cellSizeGUI.set(xmlSettings.getValue("X", 64.0f));
                xmlSettings.popTag();
                xmlSettings.popTag();
            }
            else {
                ofLog(OF_LOG_ERROR, "settings.xml does not exist");
            }
            break;
        }
        // save image
        case 'w':{
            saveFBOImage("output/screen_" + ofToString(ofGetFrameNum()) + current_font + ".jpg");
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
void ofApp::saveFBOImage(string path){

    string image_name = ofToString(path);
    ofPixels pixels;
    ofImage out_image;
    boids_fbo.getTexture().readToPixels(pixels);
    out_image.setFromPixels(pixels);
    out_image.save(image_name);
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    noiseXSpeedGUI.removeListener(this, &ofApp::changedFieldParams);
    noiseYSpeedGUI.removeListener(this, &ofApp::changedFieldParams);
    cellSizeGUI.removeListener(this, &ofApp::changedFieldParams);
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
