#include "Individual.h"
#define IMAGE_WIDTH 80
#define IMAGE_HEIGHT 60
#define GENE_SIZE 13
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
    phenotype = getPhenotype(imageWidth, imageHeight);
}
//-------------------------------------------------------
void Individual::setup(int _numOfGenes)
{
    numOfGenes = _numOfGenes;
    dna.setup(numOfGenes, geneSize);
    phenotype = getPhenotype(imageWidth, imageHeight);
}
//-------------------------------------------------------
// This function turns the floats into an image made up
// of triangles of variable colors and locations
ofImage Individual::getPhenotype(int width, int height){

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
//--------------------------------------------------------
// calculates fitness by subtracting the individual's image
// from the target image and summing up the pixel differences
void Individual::calcFitness (const ofImage &target) {

    ofPixels targetPixels = target.getPixels();
    ofPixels phenotypePixels = phenotype.getPixels();

    int totalAbsDiff = 0;
    int imageSize = target.getWidth()*target.getHeight()*3;

    for (int i=0; i<imageSize; i++){
            totalAbsDiff += abs(targetPixels[i]-phenotypePixels[i]);
    }
    fitness = (float)totalAbsDiff / (float)imageSize;
}
