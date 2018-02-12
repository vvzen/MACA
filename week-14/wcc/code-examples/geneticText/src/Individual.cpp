#include "Individual.h"

//-------------------------------------------------------
Individual::Individual(){
}
//-------------------------------------------------------
void Individual::setup(DNA _dna){
    dna = _dna;
    geneSize = dna.geneSize;
    numOfGenes = dna.numOfGenes;
    phenotype = getPhenotype();
}
//-------------------------------------------------------
void Individual::setup(int _numOfGenes)
{
    numOfGenes = _numOfGenes;
    geneSize = 1;
    dna.setup(numOfGenes, geneSize);
    phenotype = getPhenotype();
}
//-------------------------------------------------------
string Individual::getPhenotype(){
    string tempIndividual = "";
    for (int i=0;i<dna.genes.size(); i++){
        tempIndividual+=(char)ofMap(dna.genes[i], 0, 1, 32, 128);
    }
    return tempIndividual;
}
//--------------------------------------------------------
void Individual::getFitness (string target) {
     int score = 0;
     for (int i = 0; i < phenotype.length(); i++) {
        if (phenotype[i] == target[i]) {
          score++;
        }
     }
     fitness = (float)score / (float)target.length();
}
