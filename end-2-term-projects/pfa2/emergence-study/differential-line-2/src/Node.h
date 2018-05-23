#include "ofMain.h"
#include "globals.h"

class Node {

    public:

        ofPoint pos;
        ofVec2f vel, acc;

        float max_force;

        Node(){
            pos = ofPoint(0, 0, 0);
            vel = ofVec2f(ofRandom(-0.1, 0.1), ofRandom(-0.1, 0.1));
            acc = ofVec2f(0, 0);
            max_force = MAX_FORCE;
        }

        Node(ofPoint p){
            pos = p;
            vel = ofVec2f(ofRandom(-0.1, 0.1), ofRandom(-0.1, 0.1));
            acc = ofVec2f(0, 0);
            max_force = MAX_FORCE;
        }

        void flock(vector <Node*> &nodes);
        void update(vector <Node*> &nodes);
        void draw();
        
        void apply_force(ofVec2f &force);
        
        // steering behaviours
        ofVec2f seek(ofVec2f &target);
        ofVec2f get_separation(vector <Node*> &nodes);
        ofVec2f get_cohesion(vector <Node*> &nodes);
};