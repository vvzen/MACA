#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
	bikers.load("bikers.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

   	//big image
	ofSetColor(255);
    	bikers.setAnchorPercent(0,0);
	bikers.draw(0, 0);

  	//image following mouse
	bikers.setAnchorPercent(0.5,0.5);
	bikers.draw(mouseX, mouseY, bikers.getWidth()*0.3, bikers.getHeight()*0.3);

	//copied image
	copiedImg.setFromPixels(bikers.getPixels());
	copiedImg.setAnchorPercent(1,1);
	copiedImg.draw(ofGetWidth(),ofGetHeight(),bikers.getWidth()*0.2, bikers.getHeight()*0.2);
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
