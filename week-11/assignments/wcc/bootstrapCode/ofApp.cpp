#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(125);
    ofSetLineWidth(3);

    for (int i=0; i<15; i++){
        triangulation.addPoint(ofPoint(ofRandomWidth(), ofRandomHeight())); // add random points in the triangulation object of ofxDelaunay
    }
    triangulation.triangulate(); // calculate the triangulation!
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    ofSetColor(0);
    triangulation.triangleMesh.drawWireframe(); //draw the wireframe for debugging purposes

    ofFill();

    // what's important for us is to loop over the triangles and extract them. In this case
    // I wrote a helper function getTriangle(int i) which when you loop over all triangles
    // extracts the 3 points making each one and stores them in a vector called pts.
    // In this example I use pts to draw a triangle. You should use the data of the points
    // to create a FunkyTriangle object using your custom FunkyTriangle class. Create a
    // setup() function in the class to pass it the initial parameters. You'll also need a draw()
    // and later on an update(). Start by making 1 FunkyTriangle Object that has some behavior (it
    // goes from black to white and then back to white. Then create a vector of FunkyTriangles.
    // For the more daring, create a FunkyTriangleSystem so that you hide the vector and these loops
    // that might get a bit too complex after a while. See the code provided in class. It's very
    // similar to that, only you don't draw balls, you draw triangles.

    for (int g=0; g<triangulation.getNumTriangles(); g++){ // loop over the triangles
        vector <ofPoint> pts = getTriangle(g);             // extract the vector with 3 points
        ofSetColor(ofColor::fromHsb(ofRandom(255),255,150));
        ofDrawTriangle(pts[0], pts[1], pts[2]);             // use this point to draw a triangle
    }
}

//--------------------------------------------------------------
// custom function that takes an index and returns the coordinates of the triangle we refer to
vector <ofPoint> ofApp::getTriangle(int i){
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

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
