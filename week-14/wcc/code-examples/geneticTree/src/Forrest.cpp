#include "Forrest.h"

//-------------------------------------------------------
Forrest::Forrest() {
}
//-------------------------------------------------------
void Forrest::setup(float m, int num)
{
    mutationRate = m;
    trees.clear();

    for (int x=0; x<num; x++){
        Tree tempTree;
        tempTree.setup(8);
        trees.push_back(tempTree);
    }
}
//-------------------------------------------------------
// Generate a mating pool
void Forrest::selection() {
    // Clear the vector
    matingPool.clear();
    
    // Calculate total fitness of whole population
    float maxFitness=0;
    for(int i = 0; i < trees.size(); i++) maxFitness += trees[i].fitness;
    
    // Calculate fitness for each member of the population (scaled to value between 0 and 1)
    // Based on fitness, each member will get added to the mating pool a certain number of times
    // A higher fitness = more entries to mating pool = more likely to be picked as a parent
    // A lower fitness = fewer entries to mating pool = less likely to be picked as a parent
    for (int i = 0; i < trees.size(); i++) {
        float fitnessNormal = ofMap(trees[i].fitness, 0, maxFitness, 0, 1);
        int n = (int) (fitnessNormal * 100);  // Arbitrary multiplier
        for (int j = 0; j < n; j++) {
            matingPool.push_back(trees[i]);
        }
    }
}
//------------------------------------------------------------
// Create a new generation
void Forrest::draw(){
    for(int i =0; i < trees.size(); i++)
    {
        trees[i].draw(0,0); //just drawing the trees
        ofSetColor(0);
        ofDrawBitmapString(ofToString(i) + ":" + ofToString(trees[i].fitness), -10, 20);
        ofTranslate(ofGetWidth()/trees.size(), 0);
    }
}
//------------------------------------------------------------
// Create a new generation
void Forrest::generate() {
    // Refill the trees with children from the mating pool
    for (int i = 0; i < trees.size(); i++) {
      int a = int(ofRandom(matingPool.size()));
      int b = int(ofRandom(matingPool.size()));
      Tree partnerA = matingPool[a];
      Tree partnerB = matingPool[b];
      DNA childDNA = partnerA.dna.crossover(partnerB.dna);
      trees[i].calcPhenotype();
      childDNA.mutate(mutationRate);
      Tree child;
      child.setup(childDNA);
      trees[i] = child;
      trees[i].calcPhenotype();
    }
}
//------------------------------------------------------------
void Forrest::pick(int n){
     trees[n].fitness++;
}
