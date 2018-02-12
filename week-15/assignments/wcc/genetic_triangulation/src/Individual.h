#pragma once

#include "ofMain.h"
#include "DNA.h"

#define NUM_GENES 10
#define MUTATION_AMOUNT 5.0f

class Individual {

    public:
        Individual();
        
        // void setup(int imageWidth, int imageHeight);
        void setup(int _numOfGenes);
        void setup(DNA _dna);

        ofImage get_phenotype(int width, int height);
        void calculate_fitness(const ofImage & targetImage);
        // static Individual crossover(Individual tm, Individual tf);
        void mutate_genes(float mutationRate);
        
        // static const int NUM_GENES = 9;
        // static const float MUTATION_AMOUNT = 5.0f;
        DNA dna;
		int numOfGenes, geneSize;

        // float genes[NUM_GENES];
        float fitness;
        ofImage phenotype;
        int imageWidth, imageHeight;
};