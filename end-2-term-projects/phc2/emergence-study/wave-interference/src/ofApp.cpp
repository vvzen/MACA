#include "ofApp.h"

#define USE_TRIANGLE_STRIPS 1

//--------------------------------------------------------------
void ofApp::setup(){

    // 3D
    light.setPosition(ofPoint(0, 0, 150));
    light.setDirectional();

    light.lookAt(ofPoint(0, 0, 0));
    light.setOrientation(ofVec3f(219.727, 0, 0));

    cam.setDistance(80);

    // GUI
    gui.setup(); //required call
    GUI_resolution_x = 32;
    GUI_resolution_y = 32;
    GUI_frequency = 16;
    GUI_amp_factor = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // light.setOrientation(ofPoint(ofMap(mouseX, 0, ofGetWidth(), 0, 360), 0, 0));

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(255);

    // 3D STUFF
    ofEnableDepthTest();

    cam.begin();
    
    ofDrawAxis(100); // for debugging
    
    // light.enable();

    ofPushMatrix();
    // ofTranslate(-MESH_WIDTH/2, -MESH_HEIGHT/2);

    ofSetColor(255, 255, 0);
    // visualize the random "dropped" points
    for (int i = 0; i < random_points.size(); i++){
        ofDrawSphere(random_points.at(i).x, random_points.at(i).y, 1, 1);
    }

    ofSetColor(255, 120, 40);
    waves_primitive.draw();  
    ofSetColor(0);
    waves_primitive.drawWireframe();

    ofPopMatrix();

    // light.disable();
    
    cam.end();

    // 2D STUFF
    ofDisableDepthTest();

    drawImGui();
}

//--------------------------------------------------------------
void ofApp::generate_mesh(int num_cols, int num_rows, float frequency, float amplify_factor){

    waves_primitive.getMesh().clear();

    // generate a plane thanks to OF api
    ofVboMesh plane = ofMesh::plane(MESH_WIDTH, MESH_HEIGHT, num_rows, num_cols);

    cout << "generated mesh with " << waves_primitive.getMesh().getNumVertices() << " vertices" << endl;

    int num_random_points = 4;
    float max_distance = 0;

    random_points.clear();

    cout << "generating random points" << endl;
    // 2.1 find the max distance between the vertices
    // and some random chosen points on the grid
    // TODO: optimize using sort()
    for (int i = 0; i < num_random_points; i++){
        
        ofPoint random_point = ofPoint(ofRandom(-MESH_WIDTH/2, MESH_WIDTH/2), 0, ofRandom(-MESH_HEIGHT/2, MESH_HEIGHT/2));
        random_points.push_back(random_point);

        for (int p = 0; p < plane.getNumVertices(); p++){

            ofPoint mesh_point = ofPoint(plane.getVertex(p));

            float current_distance = ofDist(random_point.x, random_point.y, mesh_point.x, mesh_point.y);
            if (current_distance > max_distance){
                max_distance = current_distance;
            }
        }
    }

    cout << "applying amplitude" << endl;
    // 2.2 apply the amplitude to the y axis of the vertex
    for (int r = 0; r < random_points.size(); r++){
        
        ofPoint random_point = random_points.at(r);

        for (int i = 0; i < plane.getNumVertices(); i++){

            ofPoint mesh_point = plane.getVertex(i);
            
            float current_distance = ofDist(random_point.x, random_point.y, mesh_point.x, mesh_point.y);
            // amp gets weaker the more distant it is from the point
            float amp_strength = ofMap(current_distance, 0, max_distance, 0.5, 0);
            float current_amplitude = sin(current_distance * frequency) * amp_strength * amplify_factor;
            mesh_point.z += current_amplitude;
            
            plane.setVertex(i, mesh_point);
        }
    }

   // rotate it so that y is up
    waves_primitive.resetTransform();
    waves_primitive.rotate(90, 1, 0, 0);

    waves_primitive.getMesh() = plane;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'g'){
        generate_mesh(GUI_resolution_x, GUI_resolution_y, GUI_frequency, GUI_amp_factor);
    }
    if (key == 's'){
        waves_primitive.getMesh().save("interference.ply");
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // cout << "ofMap(mouseX, 0, ofGetWidth(), 0, 360): " << ofMap(mouseX, 0, ofGetWidth(), 0, 360) << endl;
}

//--------------------------------------------------------------
 void ofApp::drawImGui(){
     
    gui.begin();
 	
    auto main_settings = ofxImGui::Settings();
    main_settings.windowPos = ofVec2f(10, 600); // set position 
    main_settings.windowSize = ofVec2f(0.0f, 0.0f); // auto resize based on parameters dimensions
 
    ofxImGui::BeginWindow("GUI", main_settings, false);

    // generate mesh on click or when a slider is moved
    bool regenerate_mesh = false;
    
    if (ImGui::Button("Generate Mesh")) regenerate_mesh = true;

    if (ImGui::SliderInt("Resolution X", &GUI_resolution_x, 4, 128)) regenerate_mesh = true;
    if (ImGui::SliderInt("Resolution Y", &GUI_resolution_y, 4, 128)) regenerate_mesh = true;
    if (ImGui::SliderFloat("Frequency", &GUI_frequency, 0.0f, 32.0f)) regenerate_mesh = true;
    if (ImGui::SliderFloat("Amplification", &GUI_amp_factor, 0.1f, 10.0f)) regenerate_mesh = true;
    
    if (regenerate_mesh) generate_mesh(GUI_resolution_x, GUI_resolution_y, GUI_frequency, GUI_amp_factor);

    ofxImGui::EndWindow(main_settings);
    gui.end();
}