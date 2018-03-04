/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    ofSetBackgroundAuto(false);

    sampleRate 	= 48000; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */

    ofSetFrameRate(60);
    phase = 0;
    freqMod = 0;
    ampMod = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
        float newMod = ofMap(freqMod, -1, 1, -10, 10);
        phase+=newMod;

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /* You can use any of the data from audio received and audiorequested to draw stuff here.
     
     */

    // we're doing this to leave a trail of squares
    ofSetColor(255,ofMap(abs(freqMod), 0, 1, 1, 255));
    ofFill();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());

    int numOfDoors = 4;
    for (int i=0; i<numOfDoors; i++){
        door(phase + i * 180/numOfDoors);
    }
}

//--------------------------------------------------------------
void ofApp::door(float p){
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateY(p);
    float s = abs(sin(ofDegToRad(p))) + 0.3;
    ofScale(s,s,s);
    ofScale(ampMod+0.2, ampMod+0.2, ampMod+0.2);
    ofNoFill();
    ofColor c = ofColor::green.getLerped(ofColor::blue, ampMod);
    ofSetColor(c);
    ofSetLineWidth(3);
    ofDrawRectangle(0, 0, 200,200);
    ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){

         double wave;

         freqMod = osc3.triangle(.2);
         wave = osc1.sinewave(440 * osc2.sinewave(freqMod*100));

         ampMod = abs(osc4.sinewave(0.2));
         wave *= ampMod;

         output[i*nChannels    ]= wave;
         output[i*nChannels + 1]= wave;

     }    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
        
    }
    
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
