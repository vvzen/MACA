#include "FunkyTriangleSystem.h"

//--------------------------------------------------------------
void FunkyTriangleSystem::setup(){

    ofxDelaunay triangulation;

    // add random points in the triangulation object of ofxDelaunay
    int triangles_num = ofRandom(15, 20);
    for (int i = 0; i < triangles_num; i++){
        triangulation.addPoint(ofPoint(ofRandomWidth(), ofRandomHeight()));
    }
    triangulation.triangulate(); // calculate the triangulation!
    
    // add a triangle in our vector from each triangle
    // createad by the ofxDelaunay triangulation
    for (int g = 0; g < triangulation.getNumTriangles(); g++){
        
        // extract the vector with 3 points
        vector <ofPoint> pts = get_triangle_points(triangulation, g);

        FunkyTriangle tri;
        tri.setup(pts[0], pts[1], pts[2]);

        add_triangle(tri);
    }
}

//--------------------------------------------------------------
// custom function (by Theo) that takes a triangulation object and an index
// and returns the coordinates of the triangle we refer to
// (I modified it slightly so that it's more encapsulated)
vector <ofPoint> FunkyTriangleSystem::get_triangle_points(ofxDelaunay & triangulation, int i){

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
void FunkyTriangleSystem::add_triangle(FunkyTriangle tri){

    tris_vector.push_back(tri);
}

//--------------------------------------------------------------
int FunkyTriangleSystem::size(){
    return tris_vector.size();
}

//--------------------------------------------------------------
void FunkyTriangleSystem::clear(){
    tris_vector.clear();
}

//--------------------------------------------------------------
void FunkyTriangleSystem::update(){
    for (int i = 0; i < tris_vector.size(); i++){
        tris_vector.at(i).update();
    }

    cout << "modulo: " << fmod(ofGetElapsedTimef(), 5) << endl;
    // cout << "millis: " << ofGetElapsedTimeMillis() << endl;

    bool trigger = fmod(ofGetElapsedTimef(), 5) > 0.0f && fmod(ofGetElapsedTimef(), 5) < 0.02f;

    // bool trigger = ofGetElapsedTimeMillis() % 5000 == 0;

    if (trigger){
       clear();
       setup();
    }
}

//--------------------------------------------------------------
void FunkyTriangleSystem::draw(){
    for (int i = 0; i < tris_vector.size(); i++){
        tris_vector.at(i).draw();
    }
}
