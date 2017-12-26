#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    font.load("arial", 100, false, false, true);
    sentence = "Goldsmiths";
    string_points = getStringPoints(sentence, 100); // stringPoints contains now the points that make up the word "Goldsmiths"

    for (int i = 0; i < string_points.size(); i++){

        noise_seeds.push_back(ofRandom(0, 1000));
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate((ofGetWidth() - font.stringWidth(sentence)) / 2, 250);

    // ofBeginShape();
    // ofNoFill();
    // ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    for (int i = 0; i < string_points.size(); i++){

        float offset_x  = ofNoise(noise_seeds[i]) * 15;
        float offset_y  = ofNoise(noise_seeds[i] + 55) * 15;
        
        ofPoint offset = ofPoint(offset_x, offset_y);
        // ofVertex(p);
        ofPoint new_pos = string_points[i] + offset;

        ofDrawCircle(new_pos.x, new_pos.y, 2, 2);
    }
    // ofEndShape();
    ofPopMatrix();
}

//--------------------------------------------------------------
vector <ofPoint> ofApp::getStringPoints(string s, int numOfSamples){

    vector <ofPoint> stringPoints;
    vector <ofTTFCharacter> paths = font.getStringAsPoints(s);

    // find the biggest character in terms of perimeter (used for uniform resampling)
    int maxPerimeter = 0;
    for (int i = 0; i < paths.size(); i++){
       vector <ofPolyline> polylines = paths[i].getOutline();
       for (int j = 0; j < polylines.size(); j++){
           if (polylines[j].getPerimeter() > maxPerimeter) maxPerimeter = polylines[j].getPerimeter();
       }
    }
    // for every character, get its path
    for (int i = 0; i < paths.size(); i++){
        // for every character break it out to polylines
        vector <ofPolyline> polylines = paths[i].getOutline();
        // for every polyline, resample it
        for (int j = 0; j < polylines.size(); j++){
            int numOfPoints = ofMap(polylines[j].getPerimeter(), 0, maxPerimeter, 0, numOfSamples, true);
            for (int i=0; i<numOfPoints; i++){
                 stringPoints.push_back(ofPoint(polylines[j].getPointAtPercent(float(i+1)/numOfPoints)));
            }
        }
      }
     return stringPoints;
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
