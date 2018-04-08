#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(8, 8, 8);
    ofEnableDepthTest();

    earthLoc = ofVec3f(400, 0, 0);

    setupSolarSystem();

    starsMesh.setMode(OF_PRIMITIVE_POINTS);
    for(int i = 0; i < 2000; i++){
        ofPoint starLoc = ofPoint(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
        starLoc.normalize();
        starLoc *= 2000;
        starsMesh.addVertex(starLoc);
        starsMesh.addColor(ofColor(255));
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    earthLoc.x = cos(ofGetFrameNum() * 0.05) * 400;
    earthLoc.z = sin(ofGetFrameNum() * 0.05) * 400;

    cout << "earthLoc.x in update(): " << earthLoc.x << endl;
    // cout << "earthLoc.z" << earthLoc.z << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();

    ofMaterial starsMat;
    starsMat.setEmissiveColor(ofFloatColor(1.0, 1.0, 1.0));
    starsMat.begin();
    glPointSize(2);
    starsMesh.drawVertices();
    starsMat.end();


    ofDrawGrid(100.0f);

    light.setGlobalPosition(0, 0, 0);
    light.enable();

    drawSolarSystem();

    light.disable();

    cam.end();
}

//--------------------------------------------------------------
void ofApp::setupSolarSystem(){

    earthTex.loadImage("textures/earthTexture.jpg");

    sun.set(100, 60);
    sun.setPosition(0, 0, 0);
    
    earth.mapTexCoords(0, earthTex.getHeight(), earthTex.getWidth(), 0);
    earth.set(50, 100);
    earth.setGlobalPosition(earthLoc);

}

//--------------------------------------------------------------
void ofApp::drawSolarSystem(){
    
    ofEnableDepthTest();

    sunMat.begin();
    
    sunMat.setEmissiveColor(ofColor(253, 184, 19));
    sun.draw();

    sunMat.end();

    // cout << "earthLoc.x in drawSolarSystem(): " << earth.getPosition().x << endl;

    planetMat.begin();
    planetMat.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));

    earth.setGlobalPosition(earthLoc);
    earthTex.getTexture().bind();
    // earth.draw();
    earthTex.getTexture().unbind();

    cam.setGlobalPosition(earthLoc);
    cam.lookAt(ofVec3f(0, 0, 0));

    planetMat.end();

    ofDisableDepthTest();
}