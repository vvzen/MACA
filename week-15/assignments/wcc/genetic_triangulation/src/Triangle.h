#pragma once

#include "ofMain.h"

class Triangle {

    public:
        Triangle();
        
        void setup();
        void draw();
        void mutateGenes();

        Triangle crossover(Triangle tm, Triangle tf);
        ofImage getPhenotype(int width, int height);
        void calculate_fitness(const ofImage & targetImage);
        
        // x1y1x2y2x3y3rgb
        const int NUM_GENES = 9;
        const float MUTATION_AMOUNT = 5;
        float genes[NUM_GENES];
        float fitness;
};