#include "DNA.h"

DNA::DNA(){

}
//-------------------------------------------------------
void DNA::setup(int _numOfGenes, int _geneSize)
{
    numOfGenes = _numOfGenes;
    geneSize = _geneSize;

    for (int i = 0; i < numOfGenes; i++) {
        for (int j = 0; j < geneSize; j++){
            genes.push_back(ofRandom(1));
        }
    }
}
//------------------------------------------------------------------
// Crossover
DNA DNA::crossover(DNA partner) {
    // A new child
    DNA child;
    child.setup(numOfGenes, geneSize);
    int midpoint = int(ofRandom(genes.size())); // Pick a midpoint

    // Half from one, half from the other
    for (int i = 0; i < genes.size(); i++) {
      if (i > midpoint) child.genes[i] = genes[i];
      else              child.genes[i] = partner.genes[i];
    }
    return child;
}
//------------------------------------------------------------------
void DNA::mutate(float mutationRate) {
    for (int i = 0; i < genes.size(); i++) {
      if (ofRandom(1) < mutationRate) {
        genes[i] = ofRandom(1);
      }
   }
}
