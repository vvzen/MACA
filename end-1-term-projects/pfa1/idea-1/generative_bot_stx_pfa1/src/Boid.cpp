//
//  Boid.cpp
//  generative_bot_ftx
//
//  Created by Valerio Viperino
//
//

#include "boid.hpp"

// Constructor
Boid::Boid(){}

float Boid::max_force = 10.0f;
float Boid::max_steer = 2.0f;
float Boid::max_speed = 5.0f;

// Getters
ofVec2f Boid::get_position(){
    return position;
}
ofVec2f Boid::get_velocity(){
    return velocity;
}
ofVec2f Boid::get_acceleration(){
    return acceleration;
}

// Setup
void Boid::setup(ofVec2f pos, ofVec2f size){
    Boid::position = pos;
    Boid::size = size;
}
// Compute all forces
void Boid::update(bool checkEdges){
    
    if(checkEdges){
        if(position.x < 0){
            position.x = OUTPUT_WIDTH;
            // position.x = ofGetWidth();
        }
        else if(position.x > OUTPUT_WIDTH){
            position.x = 0;
        }
        if(position.y < 0){
            position.y = OUTPUT_HEIGHT;
            // position.y = ofGetHeight();
        }
        else if(position.y > OUTPUT_HEIGHT){
            position.y = 0;
        }
    }
    
    previous_position = position;
    velocity.limit(max_speed);
    velocity += acceleration;
    position += velocity;
    acceleration *= 0;
}
// Render to screen
void Boid::render(ofColor color, ofFbo * fbo){

    ofPushStyle();
    fbo->begin();
        //ofBackground(12);
        ofSetColor(color);
        ofFill();
        // ofDrawEllipse(position.x, position.y, 1, 1);
        ofDrawLine(position.x, position.y, previous_position.x, previous_position.y);
    fbo->end();
    ofPopStyle();
}

void Boid::add_force(ofVec2f force){
    force.limit(max_force);
    acceleration += force;
}
// Compute attraction to a target
// Seek: boid is always fully attracted to target
void Boid::seek(ofVec2f target){
    // Calculate vector pointing to target
    ofVec2f desiredDirection = target - position;
    // Normalize and scale it
    desiredDirection.normalize();
    desiredDirection *= max_force;
    // Apply steering formula
    // steering = desired - velocity
    ofVec2f steering = desiredDirection - velocity;
    steering.limit(max_steer);
    add_force(steering);
}

// Compute attraction to a target
// Follow: attraction desire decreases based on distance
void Boid::follow(ofVec2f target){
    // Calculate distance from target
    float targetDistance = target.distance(position);
    // Calculate vector pointing to target
    ofVec2f desiredDirection = target - velocity;
    desiredDirection.normalize();
    
    if(targetDistance < 50.0f){
        
        // The less the distance the less the desire to get there
        float desireMultiplier = ofMap(targetDistance, 0, 50, 0, 5);
        
        // scale desire according to distance
        desiredDirection *= desireMultiplier;
    }
    else {
        desiredDirection *= max_force;
    }
    // Apply steering formula
    // steering = desired - velocity
    ofVec2f steering = desiredDirection - velocity;
    steering.limit(max_steer);
    add_force(steering);
}

// Fear
// Each boid has a desire to to flee from a target
// @fearDistance : the minimum threshold distance before boids feel fear
void Boid::fear(ofVec2f target, float fearDistance){
    // Calculate distance from target
    float targetDistance = target.distance(position);
    // Calculate vector pointing away from target
    ofVec2f desiredDirection = position - target;
    desiredDirection.normalize();
    
    // If target is quite close
    if(targetDistance < fearDistance){
        
        // The less the distance the more the desire to flee away
        float desireMultiplier = ofMap(targetDistance, 0, fearDistance * 1.1, 40, 0);
        
        // scale desire according to distance
        desiredDirection *= desireMultiplier;
        
        ofVec2f steering = desiredDirection - velocity;
        steering.limit(max_steer);
        add_force(steering);
    }
}

// GROUP BEHAVIOURS

// Align
// Each boid has a desire to have the same orientation as the other boids
ofVec2f Boid::compute_alignment(vector<Boid *> boids){
    
    ofVec2f totalAlignment(0,0);
    // Sum all alignments
    for(int i = 0; i < boids.size(); i++){
        totalAlignment += boids[i]->velocity;
    }
    // Average them
    totalAlignment /= boids.size();
    // Return the averaged alignment
    ofVec2f steering = totalAlignment - velocity;
    steering.limit(max_steer);
    return steering;
}

// Separate:
// Each boid has a desire to separate from each other boid
ofVec2f Boid::compute_separation(vector<Boid *> boids, float distanceThreshold){
    
    ofVec2f totalRepulsion(0,0);
    float repulsionMag = 0;
    int boidsCount = 0;
    // Minimum distance threshold before boids want to separate themselves
    float minDistanceThreshold = distanceThreshold;
    // Loop through boids
    for(int b = 0; b < boids.size(); b++){
        // Distance of this boid from the current looped boid
        float currentBoidDistance = position.distance(boids[b]->position);
        // If the current boid is too near (and it's not this boid)
        if(currentBoidDistance > 0 && currentBoidDistance <= minDistanceThreshold){
            // Calculate vector pointing away from current boid
            ofVec2f desiredDirection = boids[b]->position - position;
            desiredDirection.normalize();
            desiredDirection *= -1;
            // Magnitude is inversely proportional to distance
            // + distance - magnitude
            repulsionMag += currentBoidDistance;
            repulsionMag /= currentBoidDistance;
            //repulsionMag *= 200;
            // Add up to total repulsion
            totalRepulsion += desiredDirection;
            boidsCount++;
        }
    }
    // Apply averaged repulsion force
    if(boidsCount > 0){
        // Calculate average
        totalRepulsion /= boidsCount;
        ofVec2f steering = totalRepulsion - velocity;
        steering.limit(max_steer);
        return steering;
    }
    else {
        return ofVec2f(0,0);
    }
}

// Flock
// Uses alignment and separation
// The boids have a desire to act as a single organism
void Boid::flock(vector<Boid *> boids, float alignMultiplier, float sepMultiplier, float sepDistance){
    ofVec2f separation = compute_separation(boids, sepDistance);
    ofVec2f alignment = compute_alignment(boids);
    separation *= sepMultiplier;
    alignment *= alignMultiplier;
    add_force(separation);
    add_force(alignment);
}