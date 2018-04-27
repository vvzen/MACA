#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // 3D

    ofSetSmoothLighting(true);
    light.setPosition(0, 200, 300);
    light.setDiffuseColor(ofFloatColor(0.85f, 0.85f, 0.55f));
    light.setSpecularColor(ofFloatColor(0.5f, 0.5f, 0.5f));

    cam.setDistance(80);
    cam.lookAt(ofPoint(0, 0, 0));

    material.setDiffuseColor(ofFloatColor(0.611, 0.352, 0.949));
    // shininess is a value between 0 - 128, 128 being the most shiny
    material.setShininess(60);
    // the light highlight of the material
    material.setSpecularColor(ofColor(255, 255, 255, 255));

    // GUI
    gui.setup(); //required call
    GUI_res_x = 64;
    GUI_res_y = 64;
    GUI_frequency = 2;
    GUI_amp_factor = 1;
    GUI_falloff_decay = 0.25f;
    GUI_weight_multiplier = 2.0f;
    GUI_num_random_points = 4;
    GUI_draw_wireframe = false;
    GUI_draw_target_points = true;

    // read the csv with the points required
    load_points_from_csv("all_continents_2.csv", influence_points_mesh, influence_points, 3.3f);

    // read the geojson and create the polygonal meshes of the countries
    vv_geojson::create_world_map("world_continents_boundaries_simplified.geojson", world_meshes, 3.3f);

    influence_points_mesh.setMode(OF_PRIMITIVE_POINTS);

    glPointSize(8);
}

//--------------------------------------------------------------
void ofApp::update(){

    // light.setPosition((ofGetWidth() * 0.5f) + cos(ofGetElapsedTimef() * 0.5f) * (ofGetWidth() * 0.3f), ofGetHeight()/2, 500);
    // light.setOrientation(ofPoint(ofMap(mouseX, 0, ofGetWidth(), 0, 360), 0, 0));
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(ofColor(220),ofColor(255));

    // 3D STUFF
    ofEnableDepthTest();
    ofEnableLighting();

    cam.begin();
    
    ofDrawAxis(100); // for debugging
    
    light.enable();

    ofPushMatrix();

    if(GUI_draw_world_meshes){
        for (int i = 0; i < world_meshes.size(); i++){
            world_meshes.at(i).draw();
        }
    }

    // visualize the target points
    ofSetColor(255, 255, 0);
    if(GUI_draw_target_points) influence_points_mesh.draw();

    material.begin();

    // draw the wave mesh
    ofFill();
    ofSetColor(59, 147, 143);
    waves_primitive.draw();
    
    material.end();

    ofDisableLighting();

    // draw the wireframe if required
    ofSetColor(0, 0, 0, 50);
    if(GUI_draw_wireframe) waves_primitive.drawWireframe();

    ofPopMatrix();

    light.disable();
    
    cam.end();

    // 2D STUFF
    ofDisableDepthTest();

    drawImGui();
}

//--------------------------------------------------------------
// Load the points into the given mesh.
// @args
//      influence_mesh: a mesh which will store the influence points (used to draw them)
//      influence_points: a vector of which will store additional data about those point (pos, name, weight)
//      scale: a scale factor to be applied to the point coordinates
// @return
//      ofVec3f, the centroid of the geo created
//--------------------------------------------------------------
ofVec3f ofApp::load_points_from_csv(std::string path, ofVboMesh &influence_mesh, vector<InfluencePoint> &influence_points, float scale){

    // load file
    ofFile file(path);

    if(!file.exists()){
        cerr << "The file " + path + " is missing";
        return ofVec3f(0, 0, 0);
	}

    // create a buffer
    ofBuffer buffer(file);

    // used to later remap weight values
    long max_population, min_population = 0;

    // read file line by line
    int i = 0;
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        
        std::string line = *it;
        cout << "i: " << i << endl;

        // skip the first row which is the header
        if (i > 0){
            // split line into strings based on the comma
            vector<string> values = ofSplitString(line, ",");
            
            // a csv row is made like that: NAME,POP_MAX,CENTROID_LON,CENTROID_LAT
            // so we expect at least 4 values

            if (values.size() >= 4){

                std::string name = values.at(0).c_str();
                long current_pop = std::atol(values.at(1).c_str());

                // find the maximum and minimum values of population in order to remap the weights
                if (i == 1){
                    min_population = current_pop;
                }
                else {
                    if (current_pop < min_population) min_population = current_pop;
                }
                if (current_pop > max_population) max_population = current_pop;

                // add each coordinate pair to the mesh
                float lon = std::atof(values.at(2).c_str());
                float lat = std::atof(values.at(3).c_str());
                // convert from lon,lat to a cartesian space with Y up
                ofPoint projected_point = vv_map_projections::mercator(lon, lat, 1);
                projected_point *= scale;
                // switch Y with Z since we have Z pointing up
                // float tmp = projected_point.y;
                // projected_point.y = projected_point.z;
                // projected_point.z = tmp;

                InfluencePoint influence_pt;
                influence_pt.name = name;
                influence_pt.pos = projected_point;
                influence_pt.population = current_pop;
                influence_pt.weight = 1;
                influence_points.push_back(influence_pt);

                // ofPoint point = ofPoint(x * scale, y * scale, 0);
                influence_mesh.addVertex(projected_point);
                influence_mesh.addColor(ofFloatColor(1.0, 0.0, 0.0));

                // DEBUGGING
                cout << "name: " << name << endl;
                cout << "current_pop: " << current_pop << endl;
                
            }
        }
        i++;
	}
    cout << endl;
    // normalize the points weights knowing the min and max values of population
    for (int i = 0; i < influence_points.size(); i++){

        float current_pop = influence_points.at(i).population;
        float weight = ofMap(current_pop, min_population, max_population, 0.08, 0.57, true);
        influence_points.at(i).weight = weight;
        
        cout << "name: " << influence_points.at(i).name << endl;
        cout << "weight: " << weight << endl;
        cout << "x: " << influence_points.at(i).pos.x << ", y: " << influence_points.at(i).pos.y << ", z: " << influence_points.at(i).pos.z << endl;
    }
    cout << endl;
    cout << "min pop: " << min_population << endl;
    cout << "max pop: " << max_population << endl;

    // return centroid of the mesh
    return influence_mesh.getCentroid();
}

//--------------------------------------------------------------
void ofApp::generate_mesh(int num_cols, int num_rows, float frequency_mult, float amplify_factor, ofMesh &borders_mesh, vector<InfluencePoint> &influence_points){

    // for performance measurement
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    // clear the mesh
    waves_primitive.getMesh().clear();

    // 1. generate a plane thanks to OF api
    ofVboMesh plane = ofMesh::plane(MESH_WIDTH, MESH_HEIGHT, num_rows, num_cols, OF_PRIMITIVE_TRIANGLES);

    cout << "generated mesh with " << plane.getNumVertices() << " vertices" << endl;

    // 2.1 find the max distance between the vertices and the influence points on the grid
    // note that in order to find the max distance we don't need to loop over each point in the grid
    // we just need to check with the 4 border points (they're the diagonals so they're the most distant ones)
    
    // get the 4 border points of the plane
    ofPoint bottom_left = plane.getVertex(0);
    ofPoint top_left = ofPoint(-MESH_WIDTH/2, MESH_HEIGHT/2, 0);
    ofPoint bottom_right = ofPoint(MESH_WIDTH/2, -MESH_HEIGHT/2);
    ofPoint top_right = ofPoint(MESH_WIDTH/2, MESH_HEIGHT/2);
    
    borders_mesh.addVertex(bottom_left);
    borders_mesh.addColor(ofFloatColor(1, 0.898, 0.058)); // BOTTOM LEFT PINK
    borders_mesh.addVertex(top_left);
    borders_mesh.addColor(ofFloatColor(0.058, 1, 0.164)); // TOP LEFT GREEN
    borders_mesh.addVertex(top_right);
    borders_mesh.addColor(ofFloatColor(0.909, 0.447, 0.090)); // TOP RIGHT ORANGE
    borders_mesh.addVertex(bottom_right);
    borders_mesh.addColor(ofFloatColor(0.090, 0.909, 0.823)); // BOTTOM RIGHT CYAN
    borders_mesh.setMode(OF_PRIMITIVE_POINTS);

    float max_distance = 0;
    
    long max_population, min_population = 0;

    // an array that will store all the distances from the mesh to our points
    // float distances[plane.getNumVertices() * influence_points.size()]; // width * height

    vector <vector <float>> distances;

    for (int p = 0; p < plane.getNumVertices(); p++){
        
        ofPoint mesh_point = ofPoint(plane.getVertex(p));
        vector <float> current_point_distances;

        plane.addNormal(ofVec3f(0,0,1)); // center normal points up
        
        for (int i = 0; i < influence_points.size(); i++){

            ofPoint influence_point_pos = influence_points.at(i).pos;

            float current_distance = ofDist(influence_point_pos.x, influence_point_pos.y, influence_point_pos.z, mesh_point.x, mesh_point.y, mesh_point.z);

            if (current_distance > max_distance) max_distance = current_distance;
            if (influence_points.at(i).population > max_population) max_population = influence_points.at(i).population;
            if (influence_points.at(i).population < min_population) min_population = influence_points.at(i).population;
            
            
            // add the current distance to our vector
            // distances[p + i * plane.getNumVertices()] = current_distance;
            current_point_distances.push_back(current_distance);
        }

        distances.push_back(current_point_distances);
    }

    cout << "max distance: " << max_distance << endl;

    ofVec3f * plane_vertices = plane.getVerticesPointer();

    // 2.2 apply the amplitude to the y axis of the vertex
    for (int p = 0; p < plane.getNumVertices(); p++){
        
        // ofPoint * mesh_point = plane.getVertex(p);

        // recover the distances for this point
        vector <float> current_distances = distances.at(p);

        float current_amplitude = 0;

        for (int i = 0; i < current_distances.size(); i++){

            float strength = ofMap(current_distances.at(i), 0, max_distance * GUI_falloff_decay, 1, 0, true);
            
            // float strength = ofMap(influence_points.at(i).weight * GUI_weight_multiplier, 0, max_distance * GUI_falloff_decay, 0, 1, true);
            
            strength *= influence_points.at(i).weight * GUI_weight_multiplier;

            // float frequency = influence_points.at(i).weight * frequency_mult;
            
            float frequency = ofMap(influence_points.at(i).weight, 0, 1, 0.55, 0.17, true) * frequency_mult;

            current_amplitude += cos(current_distances.at(i) * frequency) * strength * amplify_factor;

            plane_vertices[p].z += current_amplitude;
        }
    }

    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    cout << "Time elapsed for mesh generation: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " microseconds\n" << endl;

    // rotate it so that y is up
    // waves_primitive.resetTransform();
    // waves_primitive.rotate(90, 1, 0, 0);

    waves_primitive.getMesh() = plane;
}

//--------------------------------------------------------------
// All code related to the GUI goes here.
//--------------------------------------------------------------
 void ofApp::drawImGui(){
     
    gui.begin();
 	
    auto main_settings = ofxImGui::Settings();
    main_settings.windowPos = ofVec2f(10, 450); // set position 
    main_settings.windowSize = ofVec2f(0.0f, 0.0f); // auto resize based on parameters dimensions
 
    ofxImGui::BeginWindow("GUI", main_settings, false);

    // generate mesh or points on click or when a slider is moved
    bool regenerate_mesh = false;
    bool regenerate_points = false;
    
    if (ImGui::Button("Generate Mesh")) regenerate_mesh = true;
    // if (ImGui::Button("Generate Points")) regenerate_points = true;
    if (ImGui::Button("Toggle Wireframe")) GUI_draw_wireframe = !GUI_draw_wireframe;
    if (ImGui::Button("Toggle Points")) GUI_draw_target_points = !GUI_draw_target_points;
    if (ImGui::Button("Toggle World")) GUI_draw_world_meshes = !GUI_draw_world_meshes;

    if (ImGui::SliderInt("Resolution X", &GUI_res_x, 4, 256)) regenerate_mesh = true;
    if (ImGui::SliderInt("Resolution Y", &GUI_res_y, 4, 256)) regenerate_mesh = true;
    if (ImGui::SliderFloat("Frequency", &GUI_frequency, 0.001f, 2.0f)) regenerate_mesh = true;
    if (ImGui::SliderFloat("Amplification", &GUI_amp_factor, 0.01f, 8.0f)) regenerate_mesh = true;
    if (ImGui::SliderFloat("Weight Bias", &GUI_weight_multiplier, 0.1f, 32.0f)) regenerate_mesh = true;
    if (ImGui::SliderFloat("Strength Decay", &GUI_falloff_decay, 0.001f, 1.0f)) regenerate_mesh = true;
    // if (ImGui::SliderInt("Num of Points", &GUI_num_random_points, 1, 32)) regenerate_points = true;
    
    static char filename[24] = {};
    ImGui::InputText("mesh name for export", filename, sizeof(filename));
    if (ImGui::Button("Export Mesh as .ply")) waves_primitive.getMesh().save("export/" + ofToString(filename) + ".ply");

    if (regenerate_mesh) generate_mesh(GUI_res_x, GUI_res_y, GUI_frequency, GUI_amp_factor, influence_points_mesh, influence_points);
    // if (regenerate_points){
    //     generate_mesh(GUI_res_x, GUI_res_y, GUI_frequency, GUI_amp_factor, target_points_primitive.getMesh());
    // }

    ofxImGui::EndWindow(main_settings);
    gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // cout << "ofMap(mouseX, 0, ofGetWidth(), 0, 360): " << ofMap(mouseX, 0, ofGetWidth(), 0, 360) << endl;
}

//--------------------------------------------------------------
void ofApp::exit(){

    cout << "cam coordinates: " << cam.getPosition() << endl;
    cout << "cam orientation: " << cam.getGlobalOrientation() << endl;
}