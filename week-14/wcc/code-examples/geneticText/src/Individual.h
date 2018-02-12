#pragma once
#include "ofMain.h"
#include "DNA.h"

class Individual {

	public:
		Individual();
		void setup(DNA _dna);
		void setup(int _numOfGenes);
		void draw();
        string getPhenotype();
        void getFitness (string target);
        Individual crossover(Individual partner);
        void mutate(float mutationRate);

		DNA dna;
		int numOfGenes;
		int geneSize;
        float fitness;
        string phenotype;
};
