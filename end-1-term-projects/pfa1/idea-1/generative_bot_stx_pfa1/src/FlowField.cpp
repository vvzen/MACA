//
//  FlowField.cpp
//  generative_bot_soh
//
//  Created by Valerio Viperino
//
//

#include "FlowField.hpp"
#include "ofApp.h"

// constructor
FlowField::FlowField(){}

// setup
// using cols and rows
void FlowField::setup(float cols, float rows){
    cols_num = cols;
    rows_num = rows;
    
    cell_size.set(OUTPUT_WIDTH/cols, OUTPUT_HEIGHT/rows);
    
    if (DEBUG_GRID) cout << "N of Cols: " << cols_num << "\tNum of Rows:" << rows_num << endl;
}

// getters
ofVec2f FlowField::get_cell_size(){
    return cell_size;
}

// init random vectors grid
void FlowField::init_grid(float noiseXSpeed, float noiseYSpeed, ofVec2f sizeOfCell){
    
    // setup
    cell_size.set(sizeOfCell.x, sizeOfCell.y);
    if(DEBUG_GRID) cout << "Cell Size: " << ofToString(cell_size) << endl;
    
    cols_num = OUTPUT_WIDTH / cell_size.x;
    
    rows_num = OUTPUT_HEIGHT / cell_size.y;
    if(DEBUG_GRID) cout << "N of Cols: " << cols_num << "\tNum of Rows:" << rows_num << endl;
    
    // clear grid
    if(grid.size() > 0){
        grid.clear();
    }
    
    // populate 2d grid
    float noiseYOffset = 0.0f;
    float noiseXOffset = 0.0f;
    if(DEBUG_GRID) cout << "Populating grid.." << endl;
    for(int y = 0; y <= rows_num; y++){
        
        vector<float> row;
        
        for(int x = 0; x <= cols_num; x++){
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
    // log grid values
    if(DEBUG_GRID){
        for(int y = 0; y < grid.size(); y++){
            cout << "Row n " << y << ", values: " << ofToString(grid[y]) << endl;
        }
    }
}

ofVec2f FlowField::compute_attraction(Boid * boid){
    
    ofVec2f attraction(0,0);
    
    // Calculate cell in which boid resides
    for(int y = 0; y < grid.size(); y++){
        for(int x = 0; x < grid[y].size(); x++){
            
            ofVec2f leftBound(x * get_cell_size().x, y * get_cell_size().y);
            ofVec2f rightBound((x +1) * get_cell_size().x, (y +1) * get_cell_size().y);
            
            // If boid is within current x,y bounds (is actually in the current examined cell)
            if(boid->get_position().x > leftBound.x && boid->get_position().x <= rightBound.x){
                if(boid->get_position().y > leftBound.y && boid->get_position().y <= rightBound.y){
                    // Get angle for the current position
                    float angle = grid[y][x];
                    // Convert angle to x and y
                    attraction.set(cos(angle), sin(angle));
                    attraction *= 0.5f;
                    ofVec2f steering = attraction - boid->get_velocity();
                    steering.limit(boid->max_steer);
                    return steering;
                }
            }
        }
    }
}

// Draw base grid
void FlowField::draw_grid(){
    
    ofPushStyle();
    ofSetColor(255);
    //cout << "Draw grid" << endl;
    for(int y = 0; y <= rows_num; y++){
        for(int x = 0; x <= cols_num; x++){
            ofPushMatrix();
            ofTranslate(x * cell_size.x, y * cell_size.y);
            ofNoFill();
            // Draw grid if requested for debugging
            if (SHOW_GRID) ofDrawRectangle(0, 0, cell_size.x, cell_size.y);
            // Print the angle for the current cell
            float currentAngle = grid[y][x];
            // Show grid if requested for debugging
            if(DEBUG_GRID) ofDrawBitmapString(ofToString(currentAngle), cell_size.x/2, cell_size.y/2);
            ofRotate(currentAngle);
            ofDrawLine(-cell_size.x/2, 0, +cell_size.x/2, 0);
            
            ofPopMatrix();
        }
    }
    ofPopStyle();
}

