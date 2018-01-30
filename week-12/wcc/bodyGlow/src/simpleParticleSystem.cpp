#include "simpleParticleSystem.h"
//----------------------------------------------------------------------------
// Functions that are used with ofRemove to remove particles in an optimal way
// you can ignore these
static bool shouldRemoveDead(simpleParticle p)
{
    return p.isDead();
}
static bool shouldRemoveOffScreen(simpleParticle p)
{
    if (p.loc.x>ofGetWidth() || p.loc.x<0 || p.loc.y<0 || p.loc.y>ofGetHeight()) return true;
    else return false;
}
//##############################################################################
//-----------------------------------------------
simpleParticleSystem::simpleParticleSystem()
{
    removeOffScreenParticles = true;
    removeDeadParticles = true;
}
//-----------------------------------------------
// optionally by calling this function you can set up a grid
void simpleParticleSystem::setupAsGrid(float _size, float _agingRate, float _lifespan)
{
    removeDeadParticles = false;
    gridCellSize = _size;
    lifespan = _lifespan;

    for (int y=gridCellSize/2; y <= ofGetHeight() - gridCellSize/2; y+=gridCellSize)
    {
        for (int x=gridCellSize/2; x <= ofGetWidth() - gridCellSize/2; x+=gridCellSize)
        {
            simpleParticle s(ofVec2f(x, y));
            s.radius = gridCellSize/2;
            s.agingRate = _agingRate;
            s.lifespan = lifespan;
            s.color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
            particles.push_back(s);
        }
    }
}
//--------------------------------------------
void simpleParticleSystem::addParticle(float _x, float _y)
{
    simpleParticle s(ofVec2f(_x, _y));
    particles.push_back(s);
}

//----------------------------------------------------------
void simpleParticleSystem::update()
{
        for (int i=0; i<particles.size(); i++)
        {
            particles[i].update();
        }

        if (removeDeadParticles) ofRemove(particles, shouldRemoveDead);

        if (removeOffScreenParticles) ofRemove(particles, shouldRemoveOffScreen);
}
//----------------------------------------------------------
void simpleParticleSystem::draw()
{
    ofPushStyle();
    ofFill();
    for (int i=0; i<particles.size(); i++)
    {
        ofSetColor(particles[i].color, particles[i].lifespan);
        ofRect(particles[i].loc.x, particles[i].loc.y,  particles[i].radius, particles[i].radius);
    }
    ofPopStyle();
}
//----------------------------------------------------------
void simpleParticleSystem::applyForce(ofVec2f f)
{
    for (int i=0; i<particles.size(); i++)
    {
        particles[i].applyForce(f);
    }
}
//----------------------------------------------------------
// calling this function activates the particle when in grid mode
void simpleParticleSystem::activateParticle(int x, int y)
{
    int xBox = x/gridCellSize;
    int yBox = y/gridCellSize;
    int numOfColumns = ofGetWidth()/gridCellSize;
    int index = xBox + numOfColumns * yBox;
    particles[index].lifespan = lifespan;
}
