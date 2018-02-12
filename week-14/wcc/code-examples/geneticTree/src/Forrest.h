#pragma once
#include "ofMain.h"
#include "Tree.h"

class Forrest{

  public:
    Forrest();
    void setup(float m, int num);
    void selection();
    void generate();
    void draw();
    void pick(int n);

    float mutationRate;            // Mutation rate
    vector<Tree> trees; // Vector to hold the current population
    vector<Tree> matingPool; // Vector which we will use for our "mating pool"
};
