//
//  BoidHateArea.cpp
//  generative_bot_soh
//
//  Created by Valerio Viperino on 08/09/16.
//
//

#include "FearArea.hpp"

// Constructor
FearArea::FearArea(){}

// Getters
ofVec2f FearArea::getPosition(){
    
    return position;
}

float FearArea::getSize(){
    return size;
}

// Setup
void FearArea::setup(ofVec2f pos, float size){
    
    FearArea::position = pos;
    FearArea::size = size;
}

void FearArea::render(){
    
    ofPushStyle();
    // Set red as color
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofDrawCircle(position.x, position.y, size);
    ofPopStyle();
}
