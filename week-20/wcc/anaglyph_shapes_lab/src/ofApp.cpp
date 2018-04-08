#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate( 60 );
    
    cam.setPosition( 0, 0, 10 );
    cam.lookAt( ofVec3f(0,0,0));
    cam.enableStereo();

    cam.setNearClip(-10);

    setupRandomBoxes();

    setupGrid();
}

//--------------------------------------------------------------
void ofApp::setupRandomBoxes()
{
    boxes.assign( 100, ofBoxPrimitive() );

    for( int i = 0; i < boxes.size(); i++ ) {
        ofBoxPrimitive& box = boxes[i];
        box.set( ofRandom(0.3, 0.75) );
        box.roll( ofRandom(0, 180));
        box.tilt( ofRandom(0, 180));
        float tx = ofRandom( -7, 7 );
        float ty = ofRandom( -5, 5 );
        float tz = ofRandom( -7, 7 );
        box.setPosition( tx, ty, tz );
        colors.push_back( ofColor( ofRandom(40,55), ofRandom(100, 160), ofRandom(130, 220)));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.eyeSeparation   = ofMap( ofGetMouseX(), 0, ofGetWidth(), 0, 1., true );
    cam.focalLength     = ofMap( ofGetMouseY(), 0, ofGetHeight(), 0, 100, true );
    
    cam.orbit( ofGetElapsedTimef() * 3.f, 0.2f, 10 );
}

//-----------------------------------------------------------------------
void ofApp::draw() {
    
    ofEnableDepthTest();
    ofLight light;
    light.enable();

    if( cam.isStereo() ) {
        cam.beginLeft();
    } else {
        cam.begin();
    }
    
    //drawRandomBoxes();
    drawGrid();
    
    // draw again into the right eye //
    if( cam.isStereo() ) {
        cam.beginRight();
            // drawRandomBoxes();
            drawGrid();
    }
    
    if( cam.isStereo() ) {
        cam.endStereo();
    } else {
        cam.end();
    }

    light.disable();
    ofDisableDepthTest();
    
    ofSetColor(30, 30, 30 );
    ofDrawBitmapString("Eye Separation: "+ofToString( cam.eyeSeparation, 3), 40, 40 );
    ofDrawBitmapString("Eye Focal Length: "+ofToString( cam.focalLength, 3), 40, 60 );
}
//--------------------------------------------------------------
void ofApp::drawRandomBoxes()
{
    for( int i = 0; i < boxes.size(); i++ ) {
        ofSetColor( colors[i] );
        boxes[i].draw();
        ofSetColor(30, 30, 30);
        ofLine( ofPoint(0,0,0), boxes[i].getPosition() );
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == ' ' ) {
        if( cam.isStereo() ) cam.disableStereo();
        else cam.enableStereo();
    }
    if( key == 'f' ) {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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

//--------------------------------------------------------------
void ofApp::setupGrid(){
    for (int x = -5; x <= 5; x+=2){
        for (int y = -5; y <= 5; y+=2){
            for (int z = -5; z <= 5; z+=2){
                ofBoxPrimitive box;
                box.set(0.5);
                box.setPosition(x, y, z);
                
                nodes.push_back(box);
                ofColor color = ofColor(ofRandom(40, 55), ofRandom(100, 160), ofRandom(130, 220));
                node_colors.push_back(color);
            }
        }
    }

    for (int i = 0; i < nodes.size(); i++){

        ofBoxPrimitive box = nodes.at(i);

        // check the distance
        for(int j = 0; j < nodes.size(); j++){
            
            ofBoxPrimitive compared_box = nodes.at(j);

            if(ofDist(box.getGlobalPosition().x, box.getGlobalPosition().y, box.getGlobalPosition().z,
            compared_box.getGlobalPosition().x, compared_box.getGlobalPosition().y, compared_box.getGlobalPosition().z)
            == 2.0f){
               startLine.push_back(box.getGlobalPosition());
               endLine.push_back(compared_box.getGlobalPosition());
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::drawGrid(){

    cout << "nodes.size(): " << nodes.size() << endl;

    for (int i = 0; i < nodes.size(); i++){

        ofBoxPrimitive box = nodes.at(i);
        // cout << "i: " << i << endl;
        //ofVec3f lines = nodes.at(i+2);

        ofColor box_col = node_colors.at(i);
        
        for (int c = 0; c < 6; c++){
            box.setSideColor(c, box_col);
        }

        box.draw();
    }

    for (int i = 0; i < startLine.size(); i++){
        ofDrawLine(startLine.at(i), endLine.at(i));
    }
}