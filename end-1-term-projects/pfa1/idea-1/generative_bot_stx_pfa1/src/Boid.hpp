//
//  boid.hpp
//  generative_bot_soh
//
//  Created by Valerio Viperino.
//
//
#pragma once

#include "globals.h"
#include "ofMain.h" // reference to the of library

class Boid {
    public:
    
        // Constructor
        Boid();
        // Setup with pos and size
        void setup(ofVec2f pos, ofVec2f size);
        void update(bool checkEdges);
        void render(ofColor color, ofFbo * fbo);
    
        ofVec2f get_position();
        ofVec2f get_velocity();
        ofVec2f get_acceleration();
    
        void add_force(ofVec2f force);
        void seek(ofVec2f target);
        void follow(ofVec2f target);
        void fear(ofVec2f target, float fearDistance);
    
        // Group behaviours
        ofVec2f compute_alignment(vector<Boid *> boids);
        ofVec2f compute_separation(vector<Boid *> boids, float distanceThreshold);
        ofVec2f compute_cohesion(vector<Boid *> boids);
        void flock(vector<Boid *> boids, float alignMultiplier, float sepMultiplier, float sepDistance);
    
        static float max_force;
        static float max_steer;
        static float max_speed;
    
    private:
    
        ofVec2f previous_position;
        ofVec2f position, velocity, acceleration;
        ofVec2f size;
};
