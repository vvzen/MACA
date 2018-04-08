#include "ofApp.h"

//-------------------------------------------------------------
ofApp::~ofApp() {
    
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);

    /* Maximilian stuff */
    sampleRate 			= 44100; /* Sampling Rate */
    initialBufferSize	= 512;	/* Buffer Size. you have to fill this buffer with sound*/
    mfft.setup(fftSize, 512, 256); //just a forward FFT
    oct.setup(sampleRate, fftSize/2, nAverages);
    mfccs = (double*) malloc(sizeof(double) * 13);
    //512 bins, 42 filters, 13 coeffs, min/max freq 20/20000
    mfcc.setup(512, 42, 13, 20, 20000, sampleRate);
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    ofSoundStreamSetup(2,2, this, sampleRate, initialBufferSize, 4);/* Call this last ! */

    /*rapidlib stuff will live here*/
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    ofDrawBitmapString("using 13 inputs \nfor classification", 8, 10);
    //Draw MFCC values:
    float xinc = 190.0 / 13;
    for(int i=0; i < 13; i++) {
        float height = mfccs[i] * 200.0;
        ofDrawRectangle(10 + (i*xinc),200 - height,10, height);
    }
}

//--------------------------------------------------------------
void ofApp::audioIn (float * input, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize; i++){
        wave = (input[i*2] + input[i*2+1])/2.;
        //Calculate the mfccs
        if (mfft.process(wave)) { //is the window buffer full?
            mfft.magsToDB();
            oct.calculate(mfft.magnitudesDB);
            mfcc.mfcc(mfft.magnitudes, mfccs);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
