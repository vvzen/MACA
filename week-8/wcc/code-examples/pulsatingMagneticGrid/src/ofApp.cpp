#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetBackgroundAuto(false);

    numOfXTiles = 30;
    numOfYTiles = 30;

    spacingX = ofGetWidth() / numOfXTiles;
    spacingY = ofGetHeight() / numOfYTiles;

    startingX = spacingX / 2;
    startingY = spacingY / 2;

    ofSetCircleResolution(50);
    time = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    time+=2;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0,255);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());

    for (int x=0; x<numOfXTiles; x++){
        for (int y=0; y<numOfYTiles; y++){
            int locX = startingX + spacingX * x;
            int locY = startingY + spacingY * y;

            float d = ofDist(ofGetWidth()/2, ofGetHeight()/2, locX, locY);
            float maxDist = ofDist(ofGetWidth()/2, ofGetHeight()/2, 0, 0);

            float phaseDiff = ofMap(d, 0, maxDist, 0, 360);
            float p = sin(ofDegToRad(time + phaseDiff));
            TheoCircle(locX, locY, p);

        }
    }
}

void ofApp::TheoCircle(int x, int y, float phase)
{
    ofPushMatrix();

    //apply transformations
    ofTranslate(x, y);
    int angle = ofRadToDeg(atan2(ofGetHeight()/2-y, ofGetWidth()/2-x));
    ofRotate(angle+180);
    float displacement = phase * 15;
    ofTranslate(displacement,0);
    ofSetColor(255);
    ofDrawCircle(0,0,5);

    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='s') {
        ofSaveScreen(ofToString(ofGetFrameNum()) + ".png");
    }
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
