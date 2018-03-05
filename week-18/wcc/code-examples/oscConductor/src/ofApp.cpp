#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //OSC:
    sender1.setup(HOST1, PORT1);
    sender2.setup(HOST2, PORT2);
}


//--------------------------------------------------------------
void ofApp::update(){
    long now = ofGetElapsedTimeMillis();
    long timeSinceLast = now - lastTime;
    if (timeSinceLast > waitMillis) {
        thisBeat++;
        thisBeat = thisBeat % beatDiv;
        sendOsc(thisBeat);
        lastTime = now;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    ofDrawBitmapString(":: Conductor :: Move mouse to change bpm", 10,20);
}

void ofApp::sendOsc(int beat) {
    ofxOscMessage m;
    m.setAddress("/pulse");
    m.addIntArg(beat);

    sender1.sendMessage(m);
    sender2.sendMessage(m);
    cout << "SENT"<< beat << endl;
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    sendOsc(1);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    float bpm = (float)x/400 * 1400 + 1;
    waitMillis = 1. / bpm * 60 * 1000;
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
