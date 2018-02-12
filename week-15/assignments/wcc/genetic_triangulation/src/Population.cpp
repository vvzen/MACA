#include "Population.h"
#include <algorithm>

//--------------------------------------------------------------
static bool compare(Individual t1, Individual t2){
    return (t1.fitness < t2.fitness);
}

//-------------------------------------------------------
Population::Population() {
    top_percentile_to_keep = 0.15;
}

//--------------------------------------------------------------
void Population::setup(ofImage targetImage, float mutationRate, int numMembers){

    target_image = targetImage;
    mutation_rate = mutationRate;
    individuals.clear();

    for (int i = 0; i < numMembers; i++){
        Individual individual;
        // individual.setup(targetImage.getWidth(), targetImage.getHeight());
        individual.setup(300);
        individuals.push_back(individual);
    }

    evolution_completed = false;
    num_generations = 0;
    perfect_score = 0; // perfect score = no pixel difference

    calculate_fitness();
}

//--------------------------------------------------------------
// Calculate the fitness of every individual in the population
void Population::calculate_fitness(){

    for (int i = 0; i < individuals.size(); i++){
        individuals.at(i).calculate_fitness(target_image);
    }
}

//--------------------------------------------------------------
// Pick the best individuals!
void Population::natural_selection(){

    mating_pool.clear();

    // sort the individuals based on their fitness
    sort(individuals.begin(), individuals.end(), compare);

    // keep only the top 15%
    int num_of_best_individuals = individuals.size() * top_percentile_to_keep;

    // only add those top individuals to the mating pool
    for (int i = 0; i < num_of_best_individuals; i++){
        mating_pool.push_back(individuals.at(i));
    }
}

//--------------------------------------------------------------
// Create a new population picking only the best parents!
void Population::generate(){

    for (int i = 0; i < individuals.size(); i++){
        int t_male_index = int(ofRandom(mating_pool.size()));
        int t_female_index = int(ofRandom(mating_pool.size()));

        Individual t_male = mating_pool.at(t_male_index);
        Individual t_female = mating_pool.at(t_female_index);

        // DNA child_DNA = DNA::crossover(t_male.dna, t_female.dna);
        DNA child_DNA = t_male.dna.crossover(t_female.dna);
        child_DNA.mutate(mutation_rate);

        Individual child;
        child.setup(child_DNA);

        /* // make the crossover
        Individual child = Individual::crossover(t_male, t_female);
        // some random mutations happen
        child.mutate_genes(mutation_rate); */
        
        // add child to population
        individuals.at(i) = child;
    }
    num_generations++;
}

//--------------------------------------------------------------
ofImage Population::get_best(){
    // start from the worst performance
    float world_record = 255.0f;
    int index = 0;

    for (int i = 0; i < individuals.size(); i++){
        if (individuals.at(i).fitness < world_record){
            world_record = individuals.at(i).fitness;
            index = i;
        }
    }

    if (world_record == perfect_score) evolution_completed = true;
    // return individuals.at(index).get_phenotype(target_image.getWidth(), target_image.getHeight());
    return individuals.at(index).get_phenotype(320, 240);
}

//--------------------------------------------------------------
float Population::get_average_fitness(){

    float sum = 0;

    for (int i = 0; i < individuals.size(); i++){
        sum += individuals.at(i).fitness;
    }

    return sum / individuals.size();
}