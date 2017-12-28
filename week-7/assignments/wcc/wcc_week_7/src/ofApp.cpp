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
    
    // draw polylines of font
    // outer loop is for chars
    vector <vector <ofPoint> > font_points = getStringAsPoints(font, current_text, 64);
    for (int c = 0; c < font_points.size(); c++){
        
        // cout << "c is " << c << endl;
        // ofRectangle letter_bbox = font.getStringBoundingBox(ofToString(current_text[c]), 0, 0);
        // ofPoint letter_center = letter_bbox.getCenter();

        ofPolyline line;

        // FIXME: better implementation in terms of useless repetition
        // 1. first loop is only used for adding vertices to line
        // and compute the centroid
        for (int p = 0; p < font_points[c].size(); p++){
            line.addVertex(font_points[c][p]);
        }
        ofPoint centroid = line.getCentroid2D();
        // 2. second loop is used to draw the lines
        // now that we know the centroid
        for (int p = 0; p < font_points[c].size(); p++){
            ofDrawLine(centroid, font_points[c][p]);
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

            int num_of_points = ofMap(polylines[j].getPerimeter(), 0, max_perimeter, 0, numOfSamples, true);

            for (int p = 0; p < num_of_points; p++){
                
                ofPoint current_point = ofPoint(polylines[j].getPointAtPercent(float(p+1) / num_of_points));
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
