#pragma once

#include "ofMain.h"

class Triangle {

    public:
        Triangle();
        
        void setup();
        void draw();

        Triangle crossover(Triangle tm, Triangle tf);
        
        // x1y1x2y2x3y3rgb
        const int NUM_GENES = 9;
        float genes[NUM_GENES];
        float fitness;
};