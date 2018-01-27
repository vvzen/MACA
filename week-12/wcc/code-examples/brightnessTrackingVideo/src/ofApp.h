// Example 3. Finding the Brightest Pixel in an Image

#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    // Replace this ofImage with live video, eventually
    ofVideoGrabber vidGrabber;
    int closestColorX, closestColorY;
    void mousePressed(int x, int y, int button);
    float rTarget;
    float gTarget;
    float bTarget;
    float threshold;
    void keyPressed(int key);
    int count;
};
