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
    cam.lookAt(ofPoint(0, 0, 0));

    // GUI
    gui.setup(); //required call
    GUI_resolution_x = 32;
    GUI_resolution_y = 32;
    GUI_frequency = 16;
    GUI_amp_factor = 1;
    GUI_num_random_points = 4;
    GUI_draw_wireframe = false;
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
        ofDrawSphere(random_points.at(i).x, random_points.at(i).y, random_points.at(i).z, 1);
    }

    ofSetColor(59, 147, 143);
    waves_primitive.draw();
    ofSetColor(0);
    if(GUI_draw_wireframe) waves_primitive.drawWireframe();

    ofPopMatrix();

    // light.disable();
    
    cam.end();

    // 2D STUFF
    ofDisableDepthTest();

    drawImGui();
}

//--------------------------------------------------------------
void ofApp::generate_random_points(int num){

    if (random_points.size() > 0) random_points.clear();

    // generate the random points
    for (int i = 0; i < num; i++){
        float random_x = ofRandom(-MESH_WIDTH/2, MESH_WIDTH/2);
        float random_z = ofRandom(-MESH_HEIGHT/2, MESH_HEIGHT/2);
        ofPoint random_point = ofPoint(random_x, 0, random_z);
        cout << "adding new random point: " << random_point << endl;
        random_points.push_back(random_point);
    }
}

//--------------------------------------------------------------
void ofApp::generate_mesh(int num_cols, int num_rows, float frequency, float amplify_factor){

    waves_primitive.getMesh().clear();

    // generate a plane thanks to OF api
    ofVboMesh plane = ofMesh::plane(MESH_WIDTH, MESH_HEIGHT, num_rows, num_cols, OF_PRIMITIVE_TRIANGLES);

    cout << "generated mesh with " << waves_primitive.getMesh().getNumVertices() << " vertices" << endl;

    // the greatest distance that we will found from a point on the mesh a random point 
    float max_distance = 0;

    // 2.1 find the max distance between the vertices
    // and some random chosen points on the grid
    // TODO: optimize using sort()
    for (int i = 0; i < random_points.size(); i++){
        
        ofPoint random_point = random_points.at(i);

        for (int p = 0; p < plane.getNumVertices(); p++){

            ofPoint mesh_point = ofPoint(plane.getVertex(p));

            float current_distance = ofDist(random_point.x, random_point.y, mesh_point.x, mesh_point.y);
            if (current_distance > max_distance){
                max_distance = current_distance;
            }
        }
    }

    // 2.2 apply the amplitude to the y axis of the vertex
    for (int r = 0; r < random_points.size(); r++){
        
        ofPoint random_point = random_points.at(r);

        for (int i = 0; i < plane.getNumVertices(); i++){

            ofPoint mesh_point = plane.getVertex(i);
            
            float current_distance = ofDist(random_point.x, random_point.y, random_point.z, mesh_point.x, mesh_point.y, mesh_point.z);
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
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // cout << "ofMap(mouseX, 0, ofGetWidth(), 0, 360): " << ofMap(mouseX, 0, ofGetWidth(), 0, 360) << endl;
}

//--------------------------------------------------------------
 void ofApp::drawImGui(){
     
    gui.begin();
 	
    auto main_settings = ofxImGui::Settings();
    main_settings.windowPos = ofVec2f(10, 500); // set position 
    main_settings.windowSize = ofVec2f(0.0f, 0.0f); // auto resize based on parameters dimensions
 
    ofxImGui::BeginWindow("GUI", main_settings, false);

    // generate mesh or points on click or when a slider is moved
    bool regenerate_mesh = false;
    bool regenerate_points = false;
    

    if (ImGui::Button("Generate Mesh")) regenerate_mesh = true;
    if (ImGui::Button("Generate Points")) regenerate_points = true;
    if (ImGui::Button("Wireframe")) GUI_draw_wireframe = !GUI_draw_wireframe;

    if (ImGui::SliderInt("Resolution X", &GUI_resolution_x, 4, 256)) regenerate_mesh = true;
    if (ImGui::SliderInt("Resolution Y", &GUI_resolution_y, 4, 256)) regenerate_mesh = true;
    if (ImGui::SliderFloat("Frequency", &GUI_frequency, 0.0f, 16.0f)) regenerate_mesh = true;
    if (ImGui::SliderFloat("Amplification", &GUI_amp_factor, 0.1f, 10.0f)) regenerate_mesh = true;
    if (ImGui::SliderInt("Num of Points", &GUI_num_random_points, 1, 32)) regenerate_points = true;
    
    static char filename[24] = {};
    ImGui::InputText("mesh name for export", filename, sizeof(filename));
    if (ImGui::Button("Export Mesh as .ply")) waves_primitive.getMesh().save(ofToString(filename) + ".ply");

    if (regenerate_mesh) generate_mesh(GUI_resolution_x, GUI_resolution_y, GUI_frequency, GUI_amp_factor);
    if (regenerate_points) generate_random_points(GUI_num_random_points);

    ofxImGui::EndWindow(main_settings);
    gui.end();
}

//--------------------------------------------------------------
void ofApp::exit(){
    cout << "cam coordinates: " << cam.getPosition() << endl;
    cout << "cam orientation: " << cam.getGlobalOrientation() << endl;
}