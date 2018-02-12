#pragma once
#include "ofMain.h"
#include "Individual.h"

class Population{

  public:
    Population();
    void setup(string p, float m, int num);
    void generate();
    string getBest();
    bool finished();
    void calcFitness();
    void naturalSelection();
    int getGenerations();
    float getAverageFitness();
    string allIndividuals();

    float mutationRate;           // Mutation rate
    vector<Individual> population;// Array to hold the current population
    vector<Individual> matingPool;// ArrayList which we will use for our "mating pool"
    string target;                // Target phrase
    int generations;              // Number of generations
    bool hasFinished;             // Are we finished evolving?
    int perfectScore;
};
