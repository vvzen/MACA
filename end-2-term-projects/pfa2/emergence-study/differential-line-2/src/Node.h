#include "ofMain.h"
#include "globals.h"

class Node {

    public:

        ofPoint pos;
        ofVec3f vel, acc;

        float max_force;

        Node(){
            pos = ofPoint(0, 0, 0);
            vel = ofVec3f(ofRandom(-0.1, 0.1), ofRandom(-0.1, 0.1), ofRandom(-0.1, 0.1));
            acc = ofVec3f(0, 0, 0);
            max_force = MAX_FORCE;
        }

        Node(ofPoint p){
            pos = p;
            vel = ofVec3f(ofRandom(-0.1, 0.1), ofRandom(-0.1, 0.1), ofRandom(-0.1, 0.1));
            acc = ofVec3f(0, 0, 0);
            max_force = MAX_FORCE;
        }

        void flock(vector <Node*> &nodes);
        void update(vector <Node*> &nodes);
        void draw();
        
        void apply_force(ofVec3f &force);
        
        // steering behaviours
        ofVec3f seek(ofVec3f &target);
        ofVec3f get_separation(vector <Node*> &nodes);
        ofVec3f get_cohesion(vector <Node*> &nodes);
};