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
    // pos 1
    genes[0] = ofRandom(ofGetWidth());
    genes[1] = ofRandom(ofGetHeight());
    // pos 2
    genes[2] = ofRandom(ofGetWidth());
    genes[3] = ofRandom(ofGetHeight());
    // pos 3
    genes[4] = ofRandom(ofGetWidth());
    genes[5] = ofRandom(ofGetHeight());
    // color
    genes[6] = ofRandom(255);
    genes[7] = ofRandom(255);
    genes[8] = ofRandom(255);

    fitness = 0;
}

//--------------------------------------------------------------
void Triangle::draw(){
    ofPushStyle();
    ofSetColor(ofColor(genes[6], genes[7], genes[8]));
    ofDrawTriangle(genes[0], genes[1], genes[2], genes[3], genes[4], genes[5]);
    ofPopStyle();
}