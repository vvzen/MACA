#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    drawWall(0,0,ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::drawWall(int x, int y, int w, int h){
    ofPushMatrix();
    ofTranslate(x,y);
    int numX = 20;
    int numY = 20;
    int sizeX = w/numX;
    int sizeY = h/numY;
    int startX = sizeX /2;
    int startY = sizeY /2;
    
    for (int x=0; x<numX; x++){
        for (int y=0; y<numY; y++){
            float phase = ofGetFrameNum();
            float locX = startX + x*sizeX;
            float locY = startY + y*sizeY;
            float phaseDiff = ofMap(ofDist(locX, locY, w/2, h/2), 0, w/2, 0, 180);
            drawTile(locX,locY,sizeX,phase+phaseDiff);
        }
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawTile(int x, int y, int size, float p){
    ofSetRectMode(OF_RECTMODE_CENTER);
    float height = ofMap(abs(sin(ofDegToRad(p))),0,1,5,size-5);
    ofColor c = ofColor(0);
    c.setHsb(int(p)%255, 255, 255);
    ofSetColor(c);
    ofDrawRectangle(x,y,height,height);
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
