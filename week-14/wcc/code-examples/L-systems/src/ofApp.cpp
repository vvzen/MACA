#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);

    //***EXAMPLE 1: setting the ruleset, axiom and initializing the L-System
//    Rule rule1('F', "FF+[+F-F-F]-[-F+F+F]");
//    int total_iterations = 5;
//    float length = ofGetHeight()/4;
//    float angle = 25;
//    ruleset.push_back(rule1);
//    lsys.setup("F", ruleset);

    //***EXAMPLE 2: setting the ruleset, axiom and initializing the L-System
    Rule rule1('X', "F[+X][-X]FX");
    Rule rule2('F', "FF");
    ruleset.push_back(rule1);
    ruleset.push_back(rule2);
    int total_iterations = 8;
    float length = ofGetHeight()/2;
    float angle = 25;
    lsys.setup("X", ruleset);


    //generating the L-system
    turtle.setup(lsys.getSentence(), length, angle);
    for (int i=0; i<total_iterations; i++){
        lsys.generate();
        turtle.setToDo(lsys.getSentence());
        turtle.changeLen(0.5);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth()/2, ofGetHeight());
    ofRotate(-90);
    turtle.render();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
