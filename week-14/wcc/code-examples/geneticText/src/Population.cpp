#include "Population.h"

Population::Population() {
}
//-------------------------------------------------------
void Population::setup(string p, float m, int num)
{
    target = p;
    mutationRate = m;

    for (int x=0; x<num; x++){
        Individual individual;
        individual.setup(p.length());
        population.push_back(individual);
    }
    calcFitness();
    hasFinished = false;
    generations = 0;

    perfectScore = target.length();
}
//-------------------------------------------------------
void Population::calcFitness() {
    for (int i = 0; i < population.size(); i++) {
      population[i].getFitness(target);
    }
}
//-------------------------------------------------------
// Generate a mating pool
void Population::naturalSelection() {
    // Clear the vector
    matingPool.clear();

    float maxFitness = 0;
    for (int i = 0; i < population.size(); i++) {
      if (population[i].fitness > maxFitness) {
        maxFitness = population[i].fitness;
      }
    }

    // Based on fitness, each member will get added to the mating pool a certain number of times
    // a higher fitness = more entries to mating pool = more likely to be picked as a parent
    // a lower fitness = fewer entries to mating pool = less likely to be picked as a parent
    for (int i = 0; i < population.size(); i++) {
      float fitness = ofMap(population[i].fitness,0,maxFitness,0,1);
      int n = int(fitness * 100);                // Arbitrary multiplier
      for (int j = 0; j < n; j++) {
        matingPool.push_back(population[i]);
      }
    }
}
//-------------------------------------------------------
// Create a new generation
void Population::generate() {
    // Refill the population with children from the mating pool
    for (int i = 0; i < population.size(); i++) {
      int a = int(ofRandom(matingPool.size()));
      int b = int(ofRandom(matingPool.size()));
      Individual partnerA = matingPool[a];
      Individual partnerB = matingPool[b];
      DNA childDNA = partnerA.dna.crossover(partnerB.dna);
      childDNA.mutate(mutationRate);
      Individual child;
      child.setup(childDNA);
      population[i] = child;
    }
    generations++;
}
//-------------------------------------------------------
// Compute the current "most fit" member of the population
string Population::getBest() {
    float worldrecord = 0.0f;
    int index = 0;
    for (int i = 0; i < population.size(); i++) {
      if (population[i].fitness > worldrecord) {
        index = i;
        worldrecord = population[i].fitness;
      }
    }
    if (worldrecord == perfectScore ) hasFinished = true;
    return population[index].getPhenotype();
  }
//-------------------------------------------------------
bool Population::finished() {
    return hasFinished;
}
//-------------------------------------------------------
int Population::getGenerations() {
    return generations;
}
//-------------------------------------------------------
// Compute average fitness for the population
float Population::getAverageFitness() {
    float total = 0;
    for (int i = 0; i < population.size(); i++) {
      total += population[i].fitness;
    }
    return total / (population.size());
  }
//-------------------------------------------------------
string Population::allIndividuals() {
    string everything = "";

    int popSize = population.size();
    int displayLimit = min(popSize,14);
    for (int i = 0; i < displayLimit; i++)
    {
      everything += population[i].getPhenotype() + "\n";
    }
    return everything;
}
