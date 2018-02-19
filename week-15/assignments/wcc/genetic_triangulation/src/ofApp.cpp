#include "ofApp.h"
#define FRAME_WIDTH 80
#define FRAME_HEIGHT 60
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

    // vidGrabber.setDeviceID(0);
    // vidGrabber.setDesiredFrameRate(60);
    // vidGrabber.initGrabber(320, 240);

    popmax = 150;
    mutationRate = 0.005;
    
    // target image
    target.allocate(320, 240, OF_IMAGE_COLOR);
    target.load("caravaggio_bari.jpg");

    activate = false;
}
//--------------------------------------------------------------
void ofApp::update(){
    // vidGrabber.update();

    // if (vidGrabber.isFrameNew() ) {
    //     if (!activate) target.setFromPixels(vidGrabber.getPixels());
    // }

    if (activate){
        // Generate mating pool
        population.naturalSelection();
        //Create next generation
        population.generate();
        // Calculate fitness
        population.calcFitness();
    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    target.draw(0, 0);
    if (activate) displayInfo();
}
//--------------------------------------------------------------
void ofApp::displayInfo(){
    ofImage answer = population.getBest();
    answer.draw(330,0);
    ofDrawBitmapString("total generations: " + ofToString(population.getGenerations()), 20, 260);
    ofDrawBitmapString("average fitness: " + ofToString(population.getAverageFitness()), 20, 275);
    ofDrawBitmapString("total population: " + ofToString(popmax), 20, 290);
    ofDrawBitmapString("mutation rate: " + ofToString(int(mutationRate * 100)) + "%", 20, 305);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key=='g' || key == 'G'){
        activate = !activate;
        if (activate){
            ofImage lowResTarget = target;
            lowResTarget.resize(FRAME_WIDTH, FRAME_HEIGHT);
            population.setup(lowResTarget, mutationRate, popmax);
        }
    }
}
