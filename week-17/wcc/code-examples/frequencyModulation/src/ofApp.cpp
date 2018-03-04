#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

    sampleRate 	= 48000; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {


    for (int i = 0; i < bufferSize; i++){

        double wave;

        // ==== EXAMPLE 1 ====
        // frequency moves from 440 to -440 every second (440 and -440 sound the same)
        wave = osc1.sinewave(440 * osc2.sinewave(1));

        // ==== EXAMPLE 2 ====
        // frequency moves from 340 to 540 in one second.
        //  * carrier freq = 440
        //  * modulation freq = 1
        //  * modulation index = 100
        //  wave = osc1.sinewave(440 + osc2.sinewave(1) * 100);

        // ==== EXAMPLE 3 ====
        // frequency moves from from 340 to 540 in ever increasing speeds
        //  * carrier freq = 440
        //  * modulation freq = goes from 0 to 100 in 5 seconds and suddenly drops to 0
        //  * modulation index = 100
        // wave = osc1.sinewave(440 + osc2.sinewave( osc3.phasor(0.2,0,100) )*100);

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
