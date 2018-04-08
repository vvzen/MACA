#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "maxiMFCC.h"

class ofApp : public ofBaseApp{
    
public:
    ~ofApp();/* deconsructor is very useful */
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    
    void audioIn 	(float * input, int bufferSize, int nChannels); /* input method */
    float * lAudioIn;
    int		initialBufferSize; /* buffer size */
    int		sampleRate;
    
    /* your maximilian lives here */
    double wave;
    ofxMaxiFFTOctaveAnalyzer oct;
    int nAverages = 12;
    ofxMaxiIFFT ifft;
    ofxMaxiFFT mfft;
    int fftSize = 1024;
    int bins, dataSize;
    maxiMFCC mfcc;
    double *mfccs;
        
    /* your rapidlib stuff will live here */

};
