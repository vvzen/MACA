#include "Population.h"
#include <algorithm>

//--------------------------------------------------------------
static bool compare(Triangle t1, Triangle t2){
    return (t1.fitness < t2.fitness);
}

//--------------------------------------------------------------
Population::Population(){}

//--------------------------------------------------------------
void Population::setup(ofImage targetImage, float mutationRate, int numMembers){

    mutation_rate = mutationRate;

    for (int i = 0; i < numMembers; i++){
        Triangle triangle;
        triangle.setup();
        triangles.push_back(triangles);
    }


    calculate_fitness();
}

//--------------------------------------------------------------
// Calculate the fitness of every individual in the population
void Population::calculate_fitness(){
    for (int i = 0; i < triangles.size(); i++){
        triangles.at(i).calculate_fitness(target_image);
    }
}

//--------------------------------------------------------------
// Pick the best individuals!
void Population::natural_selection(){

    mating_pool.clear();

    // sort the individuals based on their fitness
    sort(triangles.begin(), triangles.end(), compare);

    // keep only the top 15%
    int num_of_best_individuals = triangles.size() * 0.15;

    // only add those top individuals to the mating pool
    for (int i = 0; i < num_of_best_individuals; i++){
        mating_pool.push_back(triangles.at(i));
    }
}

//--------------------------------------------------------------
// Create a new population picking only the best parents!
void Population::generate(){

    // clear current population
    triangles.clear();

    for (int i = 0; i < mating_pool.size(); i++){
        int t_male_index = ofRandom(mating_pool.size());
        int t_female_index = ofRandom(mating_pool.size());

        Triangle t_male = triangles.get(t_male_index);
        Triangle t_female = triangles.get(t_female_index);

        // make the crossover
        Triangle child = Triangle.crossover(t_male, t_female);
        // some random mutations happen
        child.mutateGenes();
        
        // add child to population
        triangles.push_back(child);
    }
    num_generations++;
}