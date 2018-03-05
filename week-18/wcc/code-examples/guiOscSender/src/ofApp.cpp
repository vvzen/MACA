#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    //OSC:
    sender.setup(HOST, PORT);
    
    //GUI:
    colorButton.addListener(this,&ofApp::colorButtonPressed);
    x.addListener(this, &ofApp::xSliderChanged);
    y.addListener(this, &ofApp::ySliderChanged);
    gui.setup(); // most of the time you don't need a name
    gui.add(x.setup("Square x", 200, 0, 400));
    gui.add(y.setup("Square y", 200, 0, 400));
    gui.add(colorButton.setup("Change color"));

    bHide = true;
    

}

//--------------------------------------------------------------
void ofApp::exit(){
    colorButton.removeListener(this,&ofApp::colorButtonPressed);
    x.removeListener(this,&ofApp::xSliderChanged);
    y.removeListener(this,&ofApp::ySliderChanged);
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    
    // should the gui control hiding?
    if( bHide ){
        gui.draw();
    }

}

void ofApp::colorButtonPressed(){
    ofxOscMessage m;
    m.setAddress("/processing/changeColor");
    sender.sendMessage(m);
}

void ofApp::xSliderChanged(float & newX ){
    ofxOscMessage m;
    m.setAddress("/processing/squarePosition");
    m.addFloatArg(x);
    m.addFloatArg(y);
    sender.sendMessage(m);
}

void ofApp::ySliderChanged(float & newY) {
    ofxOscMessage m;
    m.setAddress("/processing/squarePosition");
    m.addFloatArg(x);
    m.addFloatArg(y);
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
