#include "FireworkParticle.h"

//--------------------------------------------------------------
void FireworkParticle::setup(ofPoint pos, ofVec3f vel, bool is_initial){

    position = pos;
    velocity = vel;
    acceleration = ofVec3f(0, 0, 0);
    _is_active = true;
    _is_initial = is_initial;
    lifespan = 600;
    size = ofVec3f(ofRandom(5, 50));
    start_time = ofGetElapsedTimeMillis();
    current_lifetime = 0;
}

//--------------------------------------------------------------
void FireworkParticle::update(){

    // everybody gets old, so do our particles
    current_lifetime = ofGetElapsedTimeMillis() - start_time;
    if (current_lifetime > lifespan && !_is_initial){
        _is_active = false;
    }

    ofVec3f gravity = ofVec3f(0, -0.28, 0);
    apply_force(gravity);

    velocity += acceleration;
    // apply air resistance
    // velocity *= 0.98;
    position += velocity;
    // reset acceleration
    acceleration = ofVec3f(0, 0, 0);
    if (velocity.y <= 0 && _is_initial){
        _is_active = false;
    }
}

//--------------------------------------------------------------
void FireworkParticle::apply_force(ofVec3f force){
    acceleration += force;
}

//--------------------------------------------------------------
bool FireworkParticle::is_active(){
    return _is_active;
}

//--------------------------------------------------------------
void FireworkParticle::set_active(bool val){
    _is_active = val;
}

//--------------------------------------------------------------
bool FireworkParticle::is_initial(){
    return _is_initial;
}