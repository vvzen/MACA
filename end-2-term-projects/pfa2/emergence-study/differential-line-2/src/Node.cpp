#include "Node.h"

//--------------------------------------------------------------
void Node::apply_force(ofVec2f &force){
    acc += force;
}

//--------------------------------------------------------------
void Node::flock(vector <Node*> &nodes){
    // add separation
    ofVec2f separation_force = get_separation(nodes);
    separation_force *= DESIRED_SEPARATION;
    apply_force(separation_force);
    // add cohesion
    ofVec2f cohesion_force = get_cohesion(nodes);
    cohesion_force *= DESIRED_COHESION;
    apply_force(cohesion_force);
}

//--------------------------------------------------------------
void Node::update(vector <Node*> &nodes){

    flock(nodes);

    vel += acc;
    vel.limit(MAX_SPEED);
    
    // filter out small velocities so to avoid flickering
    if (vel.length() >= 0.01f){
        pos += vel;
    }

    // cout << "vel.length(): " << ofToString(vel.length() > 1.0) << endl;

    acc = ofVec2f(0, 0);
}

//--------------------------------------------------------------
// "Leave me alone!" said the node
//--------------------------------------------------------------
ofVec2f Node::get_separation(vector <Node*> &nodes){

    ofVec2f steer(0, 0);
    int nodes_count = 0;

    // for each node, check if it's too close
    for (int i = 0; i < nodes.size(); i++){
        
        Node * other_node = nodes.at(i);
        float distance = other_node->pos.distance(this->pos);

        // cout << "distance: " << distance << endl;

        if (distance > 0 && distance < SEPARATION_DISTANCE){

            // get the vector pointing away from this one
            ofVec2f separation_force = pos - other_node->pos;
            // weight the force by the distance and add it to the steer
            separation_force.normalize();
            separation_force /= distance;
            steer += separation_force;
            nodes_count++;
        }
    }

    // compute the average direction
    if (nodes_count > 0) steer /= nodes_count;

    // implement the Reynolds formula: steering = desired - velocity
    if (steer.length() > 0){
        steer.normalize();
        steer *= MAX_SPEED; // weight it by the amount we want
        steer -= vel;
        steer.limit(MAX_FORCE);
        // steer = desired - vel;
    }
    
    return steer;
}

//--------------------------------------------------------------
// "We want to stick together!" said another node
//--------------------------------------------------------------
ofVec2f Node::get_cohesion(vector <Node*> &nodes){

    // minimum distance required to be a neighbour node
    float neighbour_distance = SEPARATION_DISTANCE / 2.0f;

    ofVec2f cohesion_force(0, 0);
    int nodes_count = 0;

    for (int i = 0; i < nodes.size(); i++){
        
        Node * other_node = nodes.at(i);
        float distance = this->pos.distance(other_node->pos);
        
        // sum the position of all neighbours
        if (distance > 0 && distance <= neighbour_distance){
            cohesion_force += other_node->pos;
            nodes_count++;
        }
    }

    // compute average
    if (nodes_count > 0){
        cohesion_force /= nodes_count;
         // return the attraction of this node towards this averaged direction
        return seek(cohesion_force);
    }
    else {
        return ofVec2f(0, 0);
    }

}

//--------------------------------------------------------------
ofVec2f Node::seek(ofVec2f &target){
    
    ofVec2f desired_force = target - pos;
    desired_force.normalize();
    desired_force *= MAX_SPEED;
    ofVec2f steer = desired_force - vel;
    steer.limit(max_force);

    return steer;
}