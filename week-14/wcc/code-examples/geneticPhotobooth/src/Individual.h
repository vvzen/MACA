#pragma once
#include "ofMain.h"
#include "DNA.h"

class Individual {

	public:
		Individual();
		void setup(DNA _dna);
		void setup(int _numOfGenes);
		void draw();
        ofImage getPhenotype(int width, int height);
        void calcFitness (const ofImage &target);
        Individual crossover(Individual partner);
        void mutate(float mutationRate);

		DNA dna;
		int numOfGenes, geneSize;
        float fitness;
        ofImage phenotype;
        int imageWidth, imageHeight;
};
