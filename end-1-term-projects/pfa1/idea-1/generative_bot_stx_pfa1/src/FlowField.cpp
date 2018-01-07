//
//  FlowField.cpp
//  generative_bot_soh
//
//  Created by Valerio Viperino
//
//

#include "FlowField.hpp"
#include "ofApp.h"

// Constructor
FlowField::FlowField(){}

// Setup
// Using cols and rows
void FlowField::setup(float cols, float rows){
    colsNum = cols;
    rowsNum = rows;
    // cellSize.set(ofGetWidth()/cols, ofGetHeight()/rows);
    cellSize.set(OUTPUT_WIDTH/cols, OUTPUT_HEIGHT/rows);
    
    if (DEBUG_GRID) cout << "N of Cols: " << colsNum << "\tNum of Rows:" << rowsNum << endl;
}

// Getters
ofVec2f FlowField::getCellSize(){
    return cellSize;
}

// Init random vectors grid
void FlowField::initGrid(float noiseXSpeed, float noiseYSpeed, ofVec2f sizeOfCell){
    
    // Setup
    cellSize.set(sizeOfCell.x, sizeOfCell.y);
    if(DEBUG_GRID) cout << "Cell Size: " << ofToString(cellSize) << endl;
    // colsNum = ofGetWidth() / cellSize.x;
    colsNum = OUTPUT_WIDTH / cellSize.x;
    // rowsNum = ofGetHeight() / cellSize.y;
    rowsNum = OUTPUT_HEIGHT / cellSize.y;
    if(DEBUG_GRID) cout << "N of Cols: " << colsNum << "\tNum of Rows:" << rowsNum << endl;
    
    // Clear grid
    if(grid.size() > 0){
        grid.clear();
    }
    
    // Populate 2d grid
    float noiseYOffset = 0.0f;
    float noiseXOffset = 0.0f;
    if(DEBUG_GRID) cout << "Populating grid.." << endl;
    for(int y = 0; y <= rowsNum; y++){
        
        vector<float> row;
        //cout << "Current row:\n" << ofToString(grid[y]) << endl << endl;
        
        for(int x = 0; x <= colsNum; x++){
            float randomAngle;
            // With random
            //randomAngle = ofRandom(360);
            // With noise:
            noiseYOffset += noiseYSpeed;
            randomAngle = ofNoise(noiseXOffset, noiseYOffset) * 360;
            row.push_back(randomAngle);
            
        }
        noiseXOffset += noiseXSpeed;
        grid.push_back(row);
    }
    // Log grid values
    if(DEBUG_GRID){
        for(int y = 0; y < grid.size(); y++){
            cout << "Row n " << y << ", values: " << ofToString(grid[y]) << endl;
        }
    }
}

ofVec2f FlowField::computeAttraction(Boid * boid){
    
    ofVec2f attraction(0,0);
    
    // Calculate cell in which boid resides
    for(int y = 0; y < grid.size(); y++){
        for(int x = 0; x < grid[y].size(); x++){
            
            ofVec2f leftBound(x * getCellSize().x, y * getCellSize().y);
            ofVec2f rightBound((x +1) * getCellSize().x, (y +1) * getCellSize().y);
            
            // If boid is within current x,y bounds (is actually in the current examined cell)
            if(boid->getPosition().x > leftBound.x && boid->getPosition().x <= rightBound.x){
                if(boid->getPosition().y > leftBound.y && boid->getPosition().y <= rightBound.y){
                    // Get angle for the current position
                    float angle = grid[y][x];
                    // Convert angle to x and y
                    attraction.set(cos(angle), sin(angle));
                    attraction *= 0.5f;
                    ofVec2f steering = attraction - boid->getVelocity();
                    steering.limit(boid->max_steer);
                    return steering;
                }
            }
        }
    }
}

// Draw base grid
void FlowField::drawGrid(){
    
    ofSetColor(255);
    //cout << "Draw grid" << endl;
    for(int y = 0; y <= rowsNum; y++){
        for(int x = 0; x <= colsNum; x++){
            ofPushMatrix();
            ofTranslate(x * cellSize.x, y * cellSize.y);
            ofNoFill();
            // Draw grid if requested for debugging
            if (SHOW_GRID) ofDrawRectangle(0, 0, cellSize.x, cellSize.y);
            // Print the angle for the current cell
            float currentAngle = grid[y][x];
            // Show grid if requested for debugging
            if(DEBUG_GRID) ofDrawBitmapString(ofToString(currentAngle), cellSize.x/2, cellSize.y/2);
            ofRotate(currentAngle);
            ofDrawLine(-cellSize.x/2, 0, +cellSize.x/2, 0);
            
            ofPopMatrix();
        }
    }
}

