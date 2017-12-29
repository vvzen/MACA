#include "ofApp.h"
#include <typeinfo>

//--------------------------------------------------------------
void ofApp::setup(){

    word_1 = "MINDFUL";
    word_2 = "ENERGIC";
    current_text = word_1;
    timer = 0.0f;

    // font
    font.load("fonts/AvenirNext-Medium-06.ttf", 110, false, false, true);

    // GUI
    gui = new ofxDatGui();
    // gui->addLabel("TEST");
    // parameters
    GUI_noise_speed.set("Noise Speed", 0.38, 0.001, 1);
    GUI_noise_amount.set("Noise Amount", 18.3, 10, 500);
    GUI_line_width.set("Line Width", 1.7, 1, 4);
    GUI_morph.set("Morph", 0.0, 0.0, 1.0);
    // sliders
    gui->addSlider(GUI_noise_speed);
    gui->addSlider(GUI_noise_amount);
    gui->addSlider(GUI_line_width);
    gui->addSlider(GUI_morph);
    // events
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    
    gui->setPosition(20, 20);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);

    ofPushStyle();
    ofPushMatrix();

    ofSetLineWidth(GUI_line_width);

    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

    timer+= 0.1f;

    cout << timer << endl;
    cout << GUI_morph << endl;

    if (timer > 5 && !morphed){
        GUI_morph.set(ofMap(sin(timer), -1, 1, 0, 1));
        if (GUI_morph > 0.98){
            morphed = true;
        }
    }
    if (timer > 20){
        GUI_morph.set(0);
        timer = 0.0f;
        morphed = false;
    }
    
    // TEXT
    ofSetColor(255);
    // center the text
    ofRectangle font_bb = font.getStringBoundingBox(current_text, 0, 0);
    ofTranslate(-font_bb.width/2, font_bb.height/2);

    // offset
    ofTranslate(-40, 0, 0);
    // wiggle effect
    float wiggle_amount_x = ofSignedNoise(ofGetFrameNum() * GUI_noise_speed/10) * GUI_noise_amount;
    float wiggle_amount_y = ofSignedNoise(ofGetFrameNum() * GUI_noise_speed/10 + 200) * GUI_noise_amount;
    ofTranslate(wiggle_amount_x, wiggle_amount_y, 0);
    // twist
    ofRotateY(-10);
    
    // draw polylines of font
    // outer loop is for chars
    vector <vector <vector <ofPoint> > > font_points_start = getStringAsPoints3DMatrix(font, word_1, 120);
    vector <vector <vector <ofPoint> > > font_points_target = getStringAsPoints3DMatrix(font, word_2, 120);

    for (int c = 0; c < font_points_start.size(); c++){

        vector <vector <ofPoint> > start_lines = font_points_start[c];
        // we're computing the centroid just once even if we've got multiple lines inside the char
        int centroid_computed = 0;
        ofVec2f start_centroid;
        ofVec2f target_centroid;

        for (int l = 0; l < start_lines.size(); l++){
            vector <ofPoint> line_points = start_lines[l];

            // FIXME: find a better implementation in terms of useless repetition!
            
            if (!centroid_computed){
                
                ofPolyline start_line;
                ofPolyline target_line;
                // this additional loop is only used for adding vertices to compute the centroid
                for (int p = 0; p < line_points.size(); p++){
                    start_line.addVertex(line_points[p]);
                    if (GUI_morph > 0) target_line.addVertex(font_points_target[c][l][p]);
                }
                start_centroid = start_line.getCentroid2D();
                if (GUI_morph > 0) target_centroid = target_line.getCentroid2D();
                centroid_computed++;
            }

            for (int p = 0; p < line_points.size(); p++){
                ofPoint current_point = line_points[p];

                if (GUI_morph == 0){
                    ofDrawLine(start_centroid.x, start_centroid.y, current_point.x, current_point.y);
                }
                else {
                    // lerp the points
                    ofVec2f target(font_points_target[c][l][p].x, font_points_target[c][l][p].y);
                    ofVec2f interpolated = current_point.getInterpolated(target, GUI_morph);
                    // lerp the centroids
                    ofVec2f interpolated_centroid = start_centroid.getInterpolated(target_centroid, GUI_morph);

                    ofDrawLine(interpolated_centroid.x, interpolated_centroid.y, interpolated.x, interpolated.y);
                }
            } 
        }
    }

    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
vector <vector <vector <ofPoint> > > ofApp::getStringAsPoints3DMatrix(ofTrueTypeFont & font, string s, int numOfSamples){
    
    vector <vector <vector <ofPoint> > > returned_points;
    // The returned structure is like that:
    // word (returned_points)
    //  |
    //  o --- character_points
    //  o --- character_points
    //  o --- character_points
    //  o --- character_points..
    //          |
    //          o --- line_points
    //          o --- line_points.. (C is composed by 1 line, D from 2 (outer and inner), B from 3 and so on..)

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
        vector <vector <ofPoint> > character_points;

        // for every polyline, resample it
        for (int j = 0; j < polylines.size(); j++){
            
            vector <ofPoint> line_points;

            // int num_of_points = ofMap(polylines[j].getPerimeter(), 0, max_perimeter, 0, numOfSamples, true);
            int num_of_points = numOfSamples;

            for (int p = 0; p < num_of_points; p++){
                
                if (character_points.size() < numOfSamples){
                    // ofPoint current_point = ofPoint(polylines[j].getPointAtPercent(float(p+1) / num_of_points));
                    ofPoint current_point = ofPoint(polylines[j].getPointAtPercent(ofMap(p, 0, num_of_points, 0, 1)));
                    
                    line_points.push_back(current_point);
                }
            }
            character_points.push_back(line_points);
        }
        // add the char vector to the returned points vector
        returned_points.push_back(character_points);
    }
    return returned_points;
}

//--------------------------------------------------------------
vector <ofPoint> ofApp::getStringAsPoints(ofTrueTypeFont & font, string s, int numOfSamples){

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
            // int numOfPoints = ofMap(polylines[j].getPerimeter(), 0, maxPerimeter, 0, numOfSamples, true);
            int numOfPoints = numOfSamples;
            for (int i=0; i<numOfPoints; i++){
                 stringPoints.push_back(ofPoint(polylines[j].getPointAtPercent(float(i+1)/numOfPoints)));
            }
        }
      }
     return stringPoints;
}

//--------------------------------------------------------------
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e){
    // cout << e.target->getName() << " : " << e.value << endl;
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
