#pragma once
#include "ofMain.h"
#include "Individual.h"

class Population{

  public:
    Population();
    void setup(ofImage p, float m, int num);
    void calcFitness();
    void naturalSelection();
    void generate();
    ofImage getBest();
    bool finished();
    int getGenerations();
    float getAverageFitness();

    float mutationRate;            // Mutation rate
    vector<Individual> individuals; // Vector to hold the current population
    vector<Individual> matingPool; // Vector which we will use for our "mating pool"
    ofImage target;                // Target image
    int generations;               // Number of generations
    bool hasFinished;              // Are we finished evolving?
    int perfectScore;
    float topPercentileToKeep;
};
