#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
    myImage.load("friendred.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

   	//big image
	ofSetColor(255);
    ofFill();
    myImage.draw(0, 0);

    //draw rect with color under mouse
    ofColor c = myImage.getColor(mouseX, mouseY);
    cout << "ofColor object: " << c << endl;
    ofSetColor(c);
    ofDrawRectangle(0, 0, 50, 50);

    // HOW DO I ACCESS THE PIXEL ARRAY????
    ofPixels pix = myImage.getPixels();
    // what next?

    //draw red rect
    ofSetColor(255);
    ofSetLineWidth(2);
    ofNoFill();
    ofDrawRectangle(0, 0, 50, 50);
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

//  solution to puzzle
//    int r = myImage.getPixels()[(myImage.getWidth()*mouseY+mouseX)*3];
//    int g = myImage.getPixels()[(myImage.getWidth()*mouseY+mouseX)*3 + 1];
//    int b = myImage.getPixels()[(myImage.getWidth()*mouseY+mouseX)*3 + 2];
//    cout << r << " " << g << " " << b << endl;

