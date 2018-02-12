#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    target = "To be or not to be.";
    popmax = 150;
    mutationRate = 0.01;
    population.setup(target, mutationRate, popmax);
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
  // Generate mating pool
  population.naturalSelection();
  //Create next generation
  population.generate();
  // Calculate fitness
  population.calcFitness();
}

//--------------------------------------------------------------
void ofApp::draw(){
  displayInfo();
}
//--------------------------------------------------------------
void ofApp::displayInfo(){
  string answer = population.getBest();
  ofDrawBitmapString("Best phrase:",20,30);
  ofDrawBitmapString(answer, 20, 75);
  ofDrawBitmapString("total generations: " + ofToString(population.getGenerations()), 20, 140);
  ofDrawBitmapString("average fitness: " + ofToString(population.getAverageFitness()), 20, 155);
  ofDrawBitmapString("total populationation: " + ofToString(popmax), 20, 170);
  ofDrawBitmapString("mutation rate: " + ofToString(int(mutationRate * 100)) + "%", 20, 185);
  ofDrawBitmapString("All phrases:\n" + population.allIndividuals(), 650, 10);
}
