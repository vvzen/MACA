#pragma once

#include "Triangle.h"
#include "ofxDelaunay.h"

class Population {

    Population();
    void setup(ofImage targetImage, float mutationRate, int numMembers);
    void calculate_fitness();
    void natural_selection();
    void generate();

    ofImage target_image;
    float mutation_rate;
    int num_generations;

    vector<Triangle> triangles;
    vector<Triangle> mating_pool;
};