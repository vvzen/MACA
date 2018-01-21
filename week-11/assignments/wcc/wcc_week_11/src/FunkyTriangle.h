#pragma once

#include "ofMain.h"

class FunkyTriangle {

    public:
        void setup(ofPoint p1, ofPoint p2, ofPoint p3, float hue);
        void update();
        void draw();

        vector <ofPoint> points;
        ofColor color;
        int color_seed;
        float color_hue;
};