#include "Triangle.h"

//--------------------------------------------------------------
static Triangle Triangle::crossover(Triangle tm, Triangle tf){
    Triangle child;

    // this decides the percentage of genes that will come from the mother or the father
    int midpoint = ofRandom(NUM_GENES);

    // pick the genes from the parents
    for (int i = 0; i < NUM_GENES; i++){
        if (i < midpoint){
            child.genes[i] = tm.genes[i];
        }
        else {
            child.genes[i] = tf.genes[i];
        }
    }

    return child;
}

//--------------------------------------------------------------
Triangle::Triangle(){}

//--------------------------------------------------------------
void Triangle::setup(){
    
    // generate random genes
    for (int i = 0; i < NUM_GENES; i++){
        genes[i] = ofRandom(1);
    }

    fitness = 0;
}

//--------------------------------------------------------------
void Triangle::mutateGenes(float mutationRate){

    for (int i = 0; i < NUM_GENES; i++){
        if (ofRandom(1) < mutationRate){
            genes[i] += ofRandom(-MUTATION_AMOUNT, MUTATION_AMOUNT);
            genes[i] = ofClamp(genes[i], 0, 1);
        }
    }
}

//--------------------------------------------------------------
ofImage Triangle::getPhenotype(int width, int height){

}


//--------------------------------------------------------------
// Calculate the fitness as the absolute distance of the values
// of the pixels in the phenotype and the target image
void Triangle::calculate_fitness(const ofImage & targetImage){

    ofPixels target_pixels = targetImage.getPixels();
    ofPixels phenotype_pixels = phenotype.getPixels();

    int total_abs_diff = 0;

    int image_size = targetImage.getWidth() + targetImage.getHeight() * 3;

    for (int i = 0; i < image_size; i++){
        total_abs_diff += abs(targetImage[i] - phenotype_pixels[i]);
    }

    fitness = (float) total_abs_diff / (float) image_size;
}

//--------------------------------------------------------------
void Triangle::draw(){
    ofPushStyle();
    ofSetColor(ofColor(genes[6], genes[7], genes[8]));
    ofDrawTriangle(genes[0], genes[1], genes[2], genes[3], genes[4], genes[5]);
    ofPopStyle();
}