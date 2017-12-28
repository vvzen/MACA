#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    current_text = "EASY";

    // font
    font.load("fonts/Futura-Medium-01.ttf", 200, false, false, true);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);


    ofPushStyle();
    ofPushMatrix();

    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    // draw center of screen for reference
    ofSetColor(255, 0, 0);
    ofDrawCircle(0, 0, 5, 5);

    // TEXT
    ofSetColor(255);
    // center the text
    ofRectangle font_bb = font.getStringBoundingBox(current_text, 0, 0);
    ofTranslate(-font_bb.width/2, font_bb.height/2);

    // offset
    ofTranslate(-50, 0, 0);
    // twist
    ofRotateY(-10);

    // get the string as paths
    font_paths = font.getStringAsPoints(current_text);

    // font.drawString(current_text, 0, 0);
    
    // draw polylines of font
    // outer loop is for chars
    vector <vector <ofPoint> > font_points = getStringAsPoints(font, current_text, 64);
    for (int c = 0; c < font_points.size(); c++){
        for (int p = 0; p < font_points[c].size(); p++){
            ofDrawCircle(font_points[c][p], 3, 3);
        }
    }

    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
vector <vector <ofPoint> > ofApp::getStringAsPoints(ofTrueTypeFont & font, string s, int numOfSamples){

    // 2d vector that for each letter contains the points
    vector <vector <ofPoint> > returned_points;
    vector <ofTTFCharacter> paths = font.getStringAsPoints(s);

    // find the biggest character in terms of perimeter (used for uniform resampling)
    int max_perimeter = 0;
    for (int i = 0; i < paths.size(); i++){
       vector <ofPolyline> polylines = paths[i].getOutline();
       for (int j = 0; j < polylines.size(); j++){
           if (polylines[j].getPerimeter() > max_perimeter) max_perimeter = polylines[j].getPerimeter();
       }
    }
    // for every character, get its path
    for (int i = 0; i < paths.size(); i++){

        // for every character break it out to polylines
        vector <ofPolyline> polylines = paths[i].getOutline();
        
        // vector to store the points of the current char
        vector <ofPoint> character_points;

        // for every polyline, resample it
        for (int j = 0; j < polylines.size(); j++){

            int numOfPoints = ofMap(polylines[j].getPerimeter(), 0, max_perimeter, 0, numOfSamples, true);

            for (int p = 0; p < numOfPoints; p++){
                
                ofPoint current_point = ofPoint(polylines[j].getPointAtPercent(float(p+1) / numOfPoints));
                character_points.push_back(current_point);
            }
        }
        // add the char vector to the returned points vector
        returned_points.push_back(character_points);
      }
     return returned_points;
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
    cout << "mouse: " << mouseX << ", " << mouseY << endl;
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
