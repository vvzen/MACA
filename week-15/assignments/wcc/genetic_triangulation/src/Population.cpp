#include "Population.h"
#include <algorithm>

static bool compare(Individual i, Individual j) {
     return (i.fitness<j.fitness);
}
//-------------------------------------------------------
Population::Population() {
    topPercentileToKeep = 0.15;
}
//-------------------------------------------------------
void Population::setup(ofImage _target, float m, int num)
{
    target = _target;
    mutationRate = m;
    individuals.clear();

    for (int x=0; x<num; x++){
        Individual tempIndividual;
        // tempIndividual.setup(300); //300 genes = 300 triangles
        tempIndividual.setup(7*17); // the more the genes the more the triangles
        individuals.push_back(tempIndividual);
    }
    calcFitness();
    hasFinished = false;
    generations = 0;
    perfectScore = 0; // perfect score = no pixel difference
}
//------------------------------------------------------------
// Calculate the fitness of every individual in the individuals
void Population::calcFitness() {
    for (int i = 0; i < individuals.size(); i++) {
      individuals[i].calcFitness(target);
    }
}

//------------------------------------------------------------
// Generate a mating pool
void Population::naturalSelection() {
    // Clear the vector
    matingPool.clear();
    sort(individuals.begin(), individuals.end(), compare);

    int numOfTopIndividuals = individuals.size() * topPercentileToKeep;

    for (int i = 0; i < numOfTopIndividuals; i++) {
           matingPool.push_back(individuals[i]);
    }
}
//------------------------------------------------------------
// Create a new generation
void Population::generate() {
    // Refill the individuals with children from the mating pool
    for (int i = 0; i < individuals.size(); i++) {
      int a = int(ofRandom(matingPool.size()));
      int b = int(ofRandom(matingPool.size()));
      Individual partnerA = matingPool[a];
      Individual partnerB = matingPool[b];
      DNA childDNA = partnerA.dna.crossover(partnerB.dna);
      childDNA.mutate(mutationRate);
      Individual child;
      child.setup(childDNA);
      individuals[i] = child;
    }
    generations++;
}
//------------------------------------------------------------
// Compute the current "most fit" member of the individuals
ofImage Population::getBest() {
    float worldrecord = 255.0f;
    int index = 0;

    for (int i = 0; i < individuals.size(); i++) {
      if (individuals[i].fitness < worldrecord) {
        index = i;
        worldrecord = individuals[i].fitness;
      }
    }
    if (worldrecord == perfectScore ) hasFinished = true;
    return individuals[index].getPhenotype(320, 240);
  }
//------------------------------------------------------------
bool Population::finished() {
    return hasFinished;
  }
//------------------------------------------------------------
int Population::getGenerations() {
    return generations;
  }
//------------------------------------------------------------
// Compute average fitness for the individuals
float Population::getAverageFitness() {
    float total = 0;
    for (int i = 0; i < individuals.size(); i++) {
      total += individuals[i].fitness;
    }
    return total / individuals.size();
}
