#include "simpleParticle.h"

//-----------------------------------------------
simpleParticle::simpleParticle(ofVec2f _loc)
{
    loc = ofVec2f(_loc);
    vel = ofVec2f(0,0);
    accel = ofVec2f(0,0);
    lifespan =  150;

    agingRate = 2;
    radius = 10;
    color = ofColor(255);

}
//------------------------------------------------------------------
void simpleParticle::applyForce(ofVec2f f)
{
    accel += f;
}
//------------------------------------------------------------------
void simpleParticle::update()
{
    vel+=accel;
    loc+=vel;
    accel*=0;

    lifespan -= agingRate;
    lifespan = ofClamp(lifespan, 0, 255);

}
//-----------------------------------------------------------------------
bool simpleParticle::isDead()
{
    if (lifespan <= 0) return true;
    else return false;
}
