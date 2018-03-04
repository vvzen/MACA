#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

    sampleRate 	= 48000; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
    freq = 220;
    amp = 1;

}

//--------------------------------------------------------------
void ofApp::update(){
    freq = ofMap(mouseX, 0, ofGetWidth(), 0, 1000);
    amp = ofMap(mouseY, 0, ofGetHeight(), 0, 1);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("up/down for amplitude (" + ofToString(amp) + ")", 20, 20);
    ofDrawBitmapString("left/right for frequency (" + ofToString(int(freq)) + ")", 20, 40);
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {

    for (int i = 0; i < bufferSize; i++){

        double wave;

        wave = osc1.sinewave(freq);
        wave = wave * amp;

        //doing it manually
        //wave = sin(globalT);
        //globalT+=1./40.;
        
        output[i*nChannels    ]= wave;
        output[i*nChannels + 1]= wave;
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
