#pragma once

#include "ofMain.h"

class FunkyTriangle {

    public:
        void setup(ofPoint p1, ofPoint p2, ofPoint p3);
        void update();
        void draw();

        vector <ofPoint> points;
        ofColor color;
        int color_seed;
};