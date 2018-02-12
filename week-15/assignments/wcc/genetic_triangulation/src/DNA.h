#pragma once
#include "ofMain.h"

class DNA{

	public:
		DNA();
		void setup(int _numOfGenes, int _geneSize);
		void draw();
        // static DNA crossover(DNA partner1, DNA partner2);
		DNA crossover(DNA partner);
        void mutate(float mutationRate);

		vector<float> genes;
		int numOfGenes;
		int geneSize;
        float fitness;
        float mutationAmount;
};
