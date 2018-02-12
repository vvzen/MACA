#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    popmax = 150;
    mutation_rate = 0.01;
    painting.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR   );
    painting.load("piet_mondrian_red_tree_320.jpg");

    activate = false;
}

//--------------------------------------------------------------
void ofApp::update(){

    if (activate){
        
        // select parents and make children!
        population.natural_selection();
        
        // create next generation
        population.generate();
        
        // compute fitness for each member
        population.calculate_fitness();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    painting.draw(0, 0);
    if (activate) displayInfo();
}

//--------------------------------------------------------------
void ofApp::displayInfo(){

    ofImage answer = population.get_best();
    answer.draw(330,0);
    ofDrawBitmapString("total generations: " + ofToString(population.num_generations), 20, 260);
    ofDrawBitmapString("average fitness: " + ofToString(population.get_average_fitness()), 20, 275);
    // ofDrawBitmapString("mutation rate: " + ofToString(int(mutation_rate * 100)) + "%", 20, 305);
}

//--------------------------------------------------------------
// custom function (by Theo) that takes a triangulation object and an index
// and returns the coordinates of the triangle we refer to
// (I modified it slightly so that it's more encapsulated)
vector <ofPoint> ofApp::get_triangle_points(ofxDelaunay & triangulation, int i){

    int pA = triangulation.triangleMesh.getIndex(i*3);
    int pB = triangulation.triangleMesh.getIndex(i*3+1);
    int pC = triangulation.triangleMesh.getIndex(i*3+2);

    ofPoint pointA = triangulation.triangleMesh.getVertex(pA);
    ofPoint pointB = triangulation.triangleMesh.getVertex(pB);
    ofPoint pointC = triangulation.triangleMesh.getVertex(pC);

    vector <ofPoint> points;
    points.push_back(pointA);
    points.push_back(pointB);
    points.push_back(pointC);
    
    return points;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key=='g' || key == 'G'){
        activate = !activate;
        if (activate){
            ofImage lowResTarget = painting;
            lowResTarget.resize(painting.getWidth(), painting.getHeight());
            population.setup(lowResTarget, mutation_rate, 100);
        }
    }
}