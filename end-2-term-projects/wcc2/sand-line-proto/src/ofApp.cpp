#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);

    sand_line.setup(ofGetWidth(), ofGetHeight(), 1, 35, SandLine::ATTRACTOR_MODE);

    cam.setDistance(100);
}

//--------------------------------------------------------------
void ofApp::update(){

    sand_line.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(0);
    ofFill();
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2, 5, 5);
    
    ofFbo * sand_line_fbo = sand_line.get_fbo_pointer();
    sand_line_fbo->draw(0, 0);

    ofPushStyle();
    ofSetColor(255);
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 10, 10);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    cout << "latest target: " << sand_line.latest_target << endl;

    switch (key){
        case '1':{
            sand_line.set_mode(SandLine::BEZIER_MODE);
            break;
        }
        case '2':{
            sand_line.set_mode(SandLine::ATTRACTOR_MODE);
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    sand_line.add_point(ofPoint(x, y));
    sand_line.set_target(ofPoint(x, y));
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
