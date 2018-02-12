#pragma once

#include "Individual.h"
#include "ofxDelaunay.h"

class Population {
    
    public:
        Population();
        void setup(ofImage targetImage, float mutationRate, int numMembers);
        void calculate_fitness();
        void natural_selection();
        void generate();
        ofImage get_best();
        float get_average_fitness();

        ofImage target_image;
        float mutation_rate;
        int perfect_score;
        int num_generations;
        bool evolution_completed;
        float top_percentile_to_keep;

        vector<Individual> individuals;
        vector<Individual> mating_pool;
};