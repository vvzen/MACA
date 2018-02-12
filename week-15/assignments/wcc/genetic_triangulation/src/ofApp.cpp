#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    painting.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR   );
    painting.load("piet_mondrian_red_tree_768.jpg");

    population = Population(0.01, 50);
}

//--------------------------------------------------------------
void ofApp::update(){

    // compute fitness for each member
    population.calculate_fitness();
    
    // select parents and make children!
    population.natural_selection();
    
    // create next generation
    population.generate();

    //population.evolve();
}

//--------------------------------------------------------------
void ofApp::draw(){

    painting.draw(0, 0);
    
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