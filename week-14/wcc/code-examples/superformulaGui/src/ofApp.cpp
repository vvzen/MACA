#include "ofApp.h"
//===============================================================================
void ofApp::setup(){
    ofEnableSmoothing();
    ofNoFill();
    ofSetColor(255, 255, 255);

    gui.setup();

    gui.add(m.setup("m", 1, 0, 30));
    gui.add(n1.setup("n1", 1, -2, 20));
    gui.add(n2.setup("n2.", 1, 0, 20));
    gui.add(n3.setup("n3", 1, 0, 20));
    gui.add(scaler.setup("size", 100, 1, 300));
    gui.add(layers.setup("layers", 1, 1, 20));
    gui.add(formulaColor.setup("shape", ofColor(255,255), ofColor(0, 0), ofColor(255, 255)));
}
//===============================================================================
void ofApp::update(){
    ofColor c(formulaColor);
    //superformula.update(2, 18, 1, 1, 200, layers, formulaColor);
    superformula.update(m, n1, n2, n3, scaler, layers, formulaColor);
}
//===============================================================================
void ofApp::draw(){
    superformula.draw(ofGetWidth()/2, ofGetHeight()/2);
    gui.draw();
}
