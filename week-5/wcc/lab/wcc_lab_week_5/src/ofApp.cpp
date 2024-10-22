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

    float noise_size = ofMap(mouseX, 0, ofGetWidth(), 0, 100);

    for (int i = 0; i < string_points.size(); i++){

        float offset_x  = ofSignedNoise(noise_seeds[i]) * noise_size;
        float offset_y  = ofSignedNoise(noise_seeds[i] + 55) * noise_size;

        float point_size = ofSignedNoise(noise_seeds[i]) * 6;

        ofColor col_1 = ofColor(234, 225, 0);
        ofColor col_2 = ofColor(193, 37, 0);
        ofColor color = col_1.getLerped(col_2, ofMap(point_size, -6, 6, 0, 1));
        
        ofSetColor(color);
        ofPoint offset = ofPoint(offset_x, offset_y);
        ofPoint new_pos = string_points[i] + offset;

        ofVertex(new_pos);
        ofDrawCircle(new_pos.x, new_pos.y, point_size, point_size);

        // increment noise seed
        noise_seeds[i] += 0.01;
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
