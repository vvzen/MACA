#pragma once

#include <vector>
#include "ofMain.h"
#include "ofxRapidLib.h"
#include "ofxHandDetector.h"

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber cam;
    ofxHandDetector hand_detector;
};
