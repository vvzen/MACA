#pragma once
#include "ofMain.h"

class simpleParticle{

	public:
        //member functions
		simpleParticle(ofVec2f _location);
        void update();
        bool isDead();
        void applyForce(ofVec2f f);

        //member variables
        string partStr;
        ofVec2f loc;
        ofVec2f vel;
        ofVec2f accel;
        float lifespan;
        float agingRate;
        ofColor color;
        int radius;
};
