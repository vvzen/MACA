#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // list devices
    vector<ofVideoDevice> devices = video_grabber.listDevices();

    for (int i = 0; i < devices.size(); i++){

        if (devices[i].bAvailable){
            ofLogNotice() << devices[i].id << " " << devices[i].deviceName;
        }
        else {
            ofLogNotice() << devices[i].id << " " << devices[i].deviceName << " - unavailable";
        }
    }

    // init webcam
    video_grabber.setDeviceID(0);
    video_grabber.setDesiredFrameRate(60);
    video_grabber.initGrabber(320, 240);

    max_buffer_size = ofGetWidth();

    // slit scanner
    slit_loc_x = video_grabber.getWidth() / 2;
    slit_loc_y = video_grabber.getHeight();

    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){

    video_grabber.update();

    if (video_grabber.isFrameNew()){
        ofImage img;
        img.setFromPixels(video_grabber.getPixels());
        img.mirror(false, true);
        image_buffer.push_front(img);
    }

    if (image_buffer.size() > max_buffer_size) image_buffer.pop_back();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
    // wait until buffer is filled with the first image
    if (image_buffer.size() > 0){
        image_buffer[0].draw(0, 0);
    }

    // draw the slit scanner line
    ofSetColor(255, 0, 0);
    ofDrawLine(slit_loc_x, 0, slit_loc_x, slit_loc_y);

    ofSetColor(255);
    for (int i = 0; i < image_buffer.size(); i++){
        
        ofPoint image_pos = ofPoint(0, slit_loc_y);
        image_buffer[i].drawSubsection(i, slit_loc_y, 1, slit_loc_y, slit_loc_x, 0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
