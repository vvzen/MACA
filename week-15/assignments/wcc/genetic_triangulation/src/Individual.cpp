#include "Individual.h"
#define IMAGE_WIDTH 80
#define IMAGE_HEIGHT 60
#define GENE_SIZE 13

//--------------------------------------------------------------
/* Individual Individual::crossover(Individual tm, Individual tf){
    Individual child;

    // this decides the percentage of genes that will come from the mother or the father
    // int midpoint = ofRandom(NUM_GENES);

    // pick the genes from the parents
    for (int i = 0; i < NUM_GENES; i++){
        if (ofRandom(1) > 0.5){
            child.genes[i] = tm.genes[i];
        }
        else {
            child.genes[i] = tf.genes[i];
        }
    }

    return child;
} */

//-------------------------------------------------------
Individual::Individual(){
    imageWidth = IMAGE_WIDTH;
    imageHeight = IMAGE_HEIGHT;
    geneSize = GENE_SIZE;
}

//-------------------------------------------------------
void Individual::setup(DNA _dna){
    dna = _dna;
    geneSize = dna.geneSize;
    numOfGenes = dna.numOfGenes;
    phenotype = get_phenotype(imageWidth, imageHeight);
}

//--------------------------------------------------------------
void Individual::setup(int _numOfGenes){
    numOfGenes = _numOfGenes;
    dna.setup(numOfGenes, geneSize);
    phenotype = get_phenotype(imageWidth, imageHeight);
}

//--------------------------------------------------------------
// void Individual::setup(int imageWidth, int imageHeight){
    
//     // generate random genes
//     for (int i = 0; i < NUM_GENES; i++){
//         genes[i] = ofRandom(1);
//     }

//     phenotype = get_phenotype(imageWidth, imageHeight);
// }

//--------------------------------------------------------------
ofImage Individual::get_phenotype(int width, int height){

    ofFbo fbo;
    fbo.allocate(width, height, GL_RGB);
    fbo.begin();
    ofBackground(0);

    for (int i=0;i<dna.genes.size(); i+=geneSize){

        int red = ofMap(dna.genes[i], 0, 1, 0, 255);
        int green = ofMap(dna.genes[i+1], 0, 1, 0, 255);
        int blue = ofMap(dna.genes[i+2], 0, 1, 0, 255);
        int alpha = ofMap(max(dna.genes[i+3]*dna.genes[i+4], 0.2f), 0, 1, 0, 255); // could just multiply by 255
        ofPoint anchor = ofPoint(ofMap(dna.genes[i+5], 0, 1, 0, width), ofMap(dna.genes[i+6], 0, 1, 0, height));
        ofPoint offset1 = ofPoint(ofMap(dna.genes[i+7], 0, 1, -width/2, width/2), ofMap(dna.genes[i+8], 0, 1, -height/2, height/2));
        ofPoint offset2 = ofPoint(ofMap(dna.genes[i+9], 0, 1, -width/2, width/2), ofMap(dna.genes[i+10], 0, 1, -height/2, height/2));
        ofPoint offset3 = ofPoint(ofMap(dna.genes[i+11], 0, 1, -width/2, width/2), ofMap(dna.genes[i+12], 0, 1, -height/2, height/2));

        ofSetColor(red, green, blue, alpha);
        ofDrawTriangle(offset1+anchor, offset2+anchor, offset3+anchor);
    }
    fbo.end();

    ofPixels pixels;
    fbo.readToPixels(pixels);
    ofImage img;
    img.setFromPixels(pixels);
    return img;
}

//--------------------------------------------------------------
// Calculate the fitness as the absolute distance of the values
// of the pixels in the phenotype and the target image
void Individual::calculate_fitness(const ofImage & targetImage){

    ofPixels target_pixels = targetImage.getPixels();
    ofPixels phenotype_pixels = phenotype.getPixels();

    int total_abs_diff = 0;

    int image_size = targetImage.getWidth() + targetImage.getHeight() * 3;

    for (int i = 0; i < image_size; i++){
        total_abs_diff += abs(target_pixels[i] - phenotype_pixels[i]);
    }

    fitness = (float) total_abs_diff / (float) image_size;
}

//--------------------------------------------------------------
/* void Individual::mutate_genes(float mutationRate){

    for (int i = 0; i < NUM_GENES; i++){
        if (ofRandom(1) < mutationRate){
            genes[i] += ofRandom(-MUTATION_AMOUNT, MUTATION_AMOUNT);
            genes[i] = ofClamp(genes[i], 0, 1);
        }
    }
} */

//--------------------------------------------------------------
// convert the actual genes into phenotypes (in this case, an image) 
/*ofImage Individual::get_phenotype(int width, int height){
    
    ofFbo fbo;
    fbo.allocate(width, height, GL_RGB);

    fbo.begin();
    ofBackground(0);

    int red = ofMap(genes[6], 0, 1, 0, 255);
    int green = ofMap(genes[7], 0, 1, 0, 255);
    int blue = ofMap(genes[8], 0, 1, 0, 255);
    int alpha = ofMap(genes[9], 0, 1, 0, 255);
    
    ofPoint p1 = ofPoint(ofMap(genes[0], 0, 1, 0, width), ofMap(genes[1], 0, 1, 0, height));
    ofPoint p2 = ofPoint(ofMap(genes[2], 0, 1, 0, width), ofMap(genes[3], 0, 1, 0, height));
    ofPoint p3 = ofPoint(ofMap(genes[4], 0, 1, 0, width), ofMap(genes[5], 0, 1, 0, height));

    ofSetColor(red, green, blue, alpha);
    ofDrawTriangle(p1, p2, p3);

    fbo.end();

    ofPixels pixels;
    fbo.readToPixels(pixels);
    ofImage img;
    img.setFromPixels(pixels);

    return img;
}
*/