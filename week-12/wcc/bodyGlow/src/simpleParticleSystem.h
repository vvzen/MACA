#pragma once
#include "ofMain.h"
#include "simpleParticle.h"

class simpleParticleSystem{

	public:
	    //class functions
        simpleParticleSystem();
        void addParticle(float _x, float _y);
        void activateParticle(int x, int y);
        void setupAsGrid(float _size, float _agingRate, float _lifespan);
        void update();
        void draw();
        void applyForce(ofVec2f f);

        //class variables
		vector <simpleParticle> particles;
        float gridCellSize;
        bool removeOffScreenParticles;
        bool removeDeadParticles;
        float lifespan;
};
