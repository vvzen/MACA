#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(60);

    // set the random seed in order to have predictable results
    // ofSeedRandom(5555);

    gui.setup();

    glPointSize(4);

    create_circle_with_nodes();

    cam.setNearClip(0.05);
    cam.setFarClip(10000);
    // cam.disableMouseInput();
}

//--------------------------------------------------------------
void ofApp::update(){

    differential_line.differentiate();
    differential_line.grow();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();

    ofBackground(255);
    ofSetColor(0);
    
    cam.begin();
    
    differential_line.draw(true, TOGGLE_POINTS);

    cam.end();

    ofDisableDepthTest();

    drawImGui();

    ofDrawBitmapString("num nodes: " + ofToString(differential_line.nodes.size()), 20, 20);
}

//--------------------------------------------------------------
void ofApp::save_mesh(){

    // save as SVG
    ofPolyline line;

    ofBeginSaveScreenAsSVG("export.svg");
    ofBeginShape();
    for (int i = 0; i < differential_line.lines_mesh.getNumVertices(); i++){
        ofPoint p = differential_line.lines_mesh.getVertex(i);
        ofVertex(p.x, p.y);
        line.addVertex(p);
    }
    line.close();
    ofEndShape();

    ofEndSaveScreenAsSVG();

    // save as PLY
    ofTessellator tessellator;
    ofMesh exported_mesh;
    tessellator.tessellateToMesh(line, OF_POLY_WINDING_ODD, exported_mesh, true);
    exported_mesh.save("export.ply");
}

//--------------------------------------------------------------
void ofApp::create_circle_with_nodes(){

    int radius = 320;
    int num_of_points = 8;
    float increment = 2*PI / num_of_points;

    for (float a = 0; a < PI*2; a+=increment){
        float x = cos(a) * radius;
        float y = sin(a) * radius;
        
        Node * node = new Node(ofPoint(x, y, 0));
        differential_line.add_node(node);
    }

}

//--------------------------------------------------------------
 void ofApp::drawImGui(){
 
    gui.begin();
 	
    auto main_settings = ofxImGui::Settings();
    main_settings.windowPos = ofVec2f(10, 510); // set position
    main_settings.windowSize = ofVec2f(0.0f, 0.0f); // auto resize based on parameters dimensions
 
    ofxImGui::BeginWindow("GUI", main_settings, false);
  
    if (ImGui::Button("Reset")){
        differential_line.reset();
        create_circle_with_nodes();
    }

    ImGui::SliderFloat("SEPARATION_DISTANCE", &SEPARATION_DISTANCE, 10.0f, 100.0f);
    ImGui::SliderFloat("MAX_SPEED", &MAX_SPEED, 0.0f, 10.0f);
    // ImGui::SliderFloat("MAX_FORCE", &MAX_FORCE, 0.0f, 20.0f);
    ImGui::SliderFloat("MAX_FORCE", &MAX_FORCE, 0.01f, 20.0f);
    ImGui::SliderFloat("DESIRED_SEPARATION", &DESIRED_SEPARATION, 0.0f, 30.0f);
    ImGui::SliderFloat("DESIRED_COHESION", &DESIRED_COHESION, 0.0f, 20.0f);
    ImGui::SliderFloat("MAX_EDGE_LENGTH", &MAX_EDGE_LENGTH, 5.0f, 100.0f);
    ImGui::SliderInt("MAX_NODES_NUM", &MAX_NODES_NUM, 10, 4000);

    if (ImGui::Button("Toggle points")) TOGGLE_POINTS = !TOGGLE_POINTS;
    if (ImGui::Button("Save")) save_mesh();
    
    ofxImGui::EndWindow(main_settings);
    gui.end();
}
