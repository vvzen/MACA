#include "ofApp.h"

#include "maximilian.h"/* include the lib */


//--------------------------------------------------------------
void ofApp::setup(){
    
    samp1.load(ofToDataPath("hihat.wav"));
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    
    /* This is stuff you always need.*/
    sampleRate 			= 44100; /* Sampling Rate */
    initialBufferSize	= 512;	/* Buffer Size. you have to fill this buffer with sound*/
    lAudioOut			= new float[initialBufferSize];/* outputs */
    rAudioOut			= new float[initialBufferSize];
    lAudioIn			= new float[initialBufferSize];/* inputs */
    rAudioIn			= new float[initialBufferSize];
    
    
    /* This is a nice safe piece of code */
    memset(lAudioOut, 0, initialBufferSize * sizeof(float));
    memset(rAudioOut, 0, initialBufferSize * sizeof(float));
    
    memset(lAudioIn, 0, initialBufferSize * sizeof(float));
    memset(rAudioIn, 0, initialBufferSize * sizeof(float));
    

    
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    ofSoundStreamSetup(2,0, this, maxiSettings::sampleRate, initialBufferSize, 4);/* Call this last ! */
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
        receiver.setup(PORT);

}



//--------------------------------------------------------------
void ofApp::update(){

    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        if(m.getAddress() == "/pulse"){
            int i = m.getArgAsInt32(0);
            samp1.setPosition(0); //start playing it again
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(abs(wave*255));
    ofDrawBitmapString(":: Player 2 ::", 10,20);

}

//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize; i++){
        wave = samp1.playOnce();
        
        //play result
        mymix.stereo(wave, outputs, 0.5);
        lAudioOut[i] = output[i*nChannels    ] = outputs[0]; /* You may end up with lots of outputs. add them here */
        rAudioOut[i] = output[i*nChannels + 1] = outputs[1];
    }
}

//--------------------------------------------------------------
void ofApp::audioReceived 	(float * input, int bufferSize, int nChannels){
    /* You can just grab this input and stick it in a double, then use it above to create output*/
    for (int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
        lAudioIn[i] = input[i*2];
        rAudioIn[i] = input[i*2+1];
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
