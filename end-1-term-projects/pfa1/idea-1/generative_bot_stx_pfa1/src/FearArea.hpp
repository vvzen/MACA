//
//  FearArea.hpp
//  generative_bot_soh
//
//  Created by Valerio Viperino on 08/09/16.
//
//
#pragma once // include this file only once

#include "globals.h"
#include <stdio.h>
#include "ofMain.h" // reference to the of library

class FearArea {
    
    public:
        // Constructor
        FearArea();
        // Getters
        ofVec2f getPosition();
        float getSize();
        // For initialisation
        void setup(ofVec2f pos, float size);
        void render();
    
    private:
        ofVec2f position;
        float size;
    
};