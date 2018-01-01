//
//  FlowField.hpp
//  generative_bot_soh
//
//  Created by Valerio Viperino on 02/09/16.
//
//

#ifndef FlowField_hpp
#define FlowField_hpp

#include <stdio.h>
#include "ofMain.h" // reference to the of library
#include "Boid.hpp"

class FlowField {
    
    public:
    
        // Constructor
        FlowField();
    
        void setup(float colsNum, float rowsNum);
        void initGrid(float xSpeed, float ySpeed, ofVec2f cellSize);
        void drawGrid();
        ofVec2f computeAttraction(Boid * boid);
    
        // Getters
        ofVec2f getCellSize();
    
        // A 2d vector array
        vector <vector<float>> grid;
    
    private:
    
        float colsNum, rowsNum;
        float cellNum;
        ofVec2f cellSize;
    
        // For debugging
        static const bool DEBUG_GRID = false;
        static const bool SHOW_GRID = false;
};

#endif /* FlowField_hpp */
