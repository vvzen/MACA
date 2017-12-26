#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(50);
    circleLoc = ofPoint(40,ofGetHeight()/2);
    circleSpeed = ofPoint(3,0);

    fbo.allocate(500,500);
}

//--------------------------------------------------------------
void ofApp::update(){
    circleLoc += circleSpeed;
    if (circleLoc.x>fbo.getWidth()-10 || circleLoc.x<10){
        circleSpeed.x *= -1;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //create a framebuffer and draw the circle in it (but don't render the buffer)
    fbo.begin();
    ofClear(255,0,255,255);
    ofDrawCircle(circleLoc,10);
    fbo.end();

    //create four 2D coordinates
    ofPoint p0 = ofPoint(mouseX, mouseY,0);
    ofPoint p1 = ofPoint(fbo.getWidth()-1,0,0);
    ofPoint p2 = ofPoint(fbo.getWidth()-1,fbo.getHeight()-1,0);
    ofPoint p3 = ofPoint(0,fbo.getHeight()-1,0);


    ofRotateY(20); // a bit of a rotation so that you see it's actually 3D (not really needed)

    //draw control points as a debugging tool
    ofDrawSphere(p0,10);
    ofDrawSphere(p1,10);
    ofDrawSphere(p2,10);
    ofDrawSphere(p3,10);

    //draw FBO in the coordinates given
    fbo.getTexture().draw(ofPoint(mouseX,mouseY),p1,p2,p3);
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
    ofNoFill();
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
