#include "ofApp.h"

// TODO:
// create a word at the center of the screen in 3d mode
// get the contour points (2d shape)
// copy them and move them on the z axis
// repeat a few times
// add all of those points to an ofMesh
// draw it and see what happens

//--------------------------------------------------------------
void ofApp::setup(){

    font.load("fonts/AndaleMono.ttf", 16, true, true, true);

    // camera stuff
    cam.setDistance(327.812);
    cam.setScale(1, -1, 1); // bug in ofEasyCam, see https://stackoverflow.com/questions/14416577/stop-the-inversion-of-y-axis-in-camera
    cam.disableMouseInput();

    // lighting
    key_light_1.setAttenuation(1.0f, 0.f, 0.001f);
    key_light_1.setPointLight();
    key_light_2.setAttenuation(1.0f, 0.f, 0.001f);
    key_light_2.setPointLight();

    // materials
    text_mat.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));
    text_mat.setShininess(0.5f);
    text_mat.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));

    ofSetSphereResolution(40);

    extrusion_depth = 2.5f;

    //////////////////////
    // START 3D DRAWING //
    //////////////////////

    available_words[0] = "#openframeworks";
    available_words[1] = "#asda";
    available_words[2] = "#ShotOniPhone";
    available_words[3] = "#nofilter";
    available_words[4] = "#instafood";

    // Step 1. fill space evenly with the words
    float current_h_offset = 0.0f;
    float current_v_offset = font.getStringBoundingBox("iAAASg", 0, 0).getHeight() + 5.0f;
    for (int y = current_v_offset*2; y < ofGetHeight(); y+=current_v_offset){
        for (int x = ofRandom(0, current_h_offset); x < ofGetWidth() - current_h_offset; x+=current_h_offset){
            
            word current_word;
            current_word.pos = ofPoint(x, y);
            current_word.text = available_words[(int) floor(ofRandom(5))];
            current_word.size = ofVec2f(
                font.getStringBoundingBox(current_word.text, 0, 0).getWidth() + 50.0f,
                font.getStringBoundingBox(current_word.text, 0, 0).getHeight());
            all_words.push_back(current_word);

            // cout << "current h offset:  " << current_h_offset << endl;
            // cout << "current v offset:  " << current_v_offset << endl;
            // cout << "current_word.text: " << current_word.text << endl;

            current_h_offset = current_word.size.x;
        }
    }
    
    // Step 2. generate the 3d words
    for (int i = 0; i < all_words.size(); i++){
        word current_word = all_words.at(i);
        // cout << "adding word at index:    " << i << endl;
        vector<ofVboMesh> current_meshes = extrude_mesh_from_text(current_word.text, font, extrusion_depth);
        all_meshes.push_back(current_meshes);
        // cout << "current all_meshes size: " << all_meshes.size() << endl;
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    // current_offset = ofMap(mouseX, 0, ofGetWidth(), 5, 1); // depth between front and back faces
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofFill();

    ofEnableDepthTest();
    
    // cam.setDistance(ofMap(mouseX, 0, ofGetWidth(), 100, 1000));
    cam.begin();
    
    // stuff for reference
    // ofDrawGrid();

    ofPushMatrix();
    // ofScale(1, -1, 1); // flip y axis
    ofTranslate(-ofGetWidth() /2, - ofGetHeight() / 2, 0);

    // 4 reference points
    /* ofSetColor(255, 0, 0);
    ofDrawSphere(0, 0, 0, 5);
    ofSetColor(255, 255, 0);
    ofDrawSphere(0, ofGetHeight(), 0, 5);
    ofSetColor(0, 255, 255);
    ofDrawSphere(ofGetWidth(), 0, 0, 5);
    ofSetColor(0, 0, 255);
    ofDrawSphere(ofGetWidth(), ofGetHeight(), 0, 5);
    ofSetColor(255); */

    // add moving light
    // key_light.lookAt(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0), ofVec3f(0, 1, 0));
    float light_x, light_y, light_z;
    light_x = mouseX;
    light_y = mouseY;
    light_z = 50;
    key_light_1.setPosition(light_x - ofGetWidth()/2 - 10, light_y - ofGetHeight()/2, light_z);
    key_light_1.enable();
    key_light_2.setPosition(light_x - ofGetWidth()/2 + 10, light_y - ofGetHeight()/2, light_z);
    key_light_2.enable();

    // ofVec3f mouse_world_pos = cam.screenToWorld(ofVec3f(mouseX, mouseY, 0), ofRectangle(ofPoint(0, 0), ofGetWidth(), ofGetHeight()));

    // ofDrawSphere(x, y, z, 4);
    // ofDrawSphere(mouse_world_pos.x, mouse_world_pos.y, mouse_world_pos.z, 4);

    for (int i = 0; i < all_words.size(); i++){
        vector <ofVboMesh> current_meshes = all_meshes.at(i);
        word current_word = all_words.at(i);

        ofPoint center_of_word = ofPoint(
            current_word.pos.x + (current_word.size.x/2),
            current_word.pos.y + (current_word.size.y/2));
        
        // ofDrawSphere(center_of_word.x, center_of_word.y, 0, 4);

        //ofVec3f mouse_world_pos = cam.screenToWorld(ofVec3f(mouseX, mouseY, 0), ofRectangle(ofPoint(0, 0), ofGetWidth(), ofGetHeight()));
    

        float mouse_distance = ofDist(center_of_word.x, center_of_word.y, 0, mouseX, mouseY, 0);

        text_mat.begin();

        ofPushMatrix();
        float z_move = 0.0f;
        float max_distance = 64;
        if (mouse_distance < 64) z_move = ofMap(mouse_distance, max_distance, 0, 0, 35);

        ofTranslate(current_word.pos.x, current_word.pos.y, z_move);

        for (int m = 0; m < current_meshes.size(); m++){
            current_meshes.at(m).draw();
        }
        ofPopMatrix();

        text_mat.end();
    }
    
    ofPopMatrix();

    cam.end();

    key_light_1.disable();
    key_light_2.disable();

   ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    // cout << "mouse: " << x << ", " << y << endl;
    // cout << ofMap(162, 0, ofGetWidth(), 100, 1000) << endl;
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
