//
//  FlowField.hpp
//  generative_bot_soh
//
//  Created by Valerio Viperino on 02/09/16.
//
//
#pragma once // include this file only once

#include "globals.h"
#include "ofMain.h" // reference to the of library
#include "boid.hpp"

class FlowField {
    
    public:
    
        // Constructor
        FlowField();
    
        void setup(float cols_num, float rows_num);
        void init_grid(float xSpeed, float ySpeed, ofVec2f cell_size);
        void draw_grid();
        ofVec2f compute_attraction(Boid * boid);
    
        // Getters
        ofVec2f get_cell_size();
    
        // A 2d vector array
        vector <vector<float>> grid;
    
    private:
    
        float cols_num, rows_num;
        ofVec2f cell_size;
    
        // For debugging
        static const bool DEBUG_GRID = false;
        static const bool SHOW_GRID = false;
};