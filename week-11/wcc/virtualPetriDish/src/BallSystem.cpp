#include "BallSystem.h"

//-------------------------------------------------------
BallSystem::BallSystem()
{

}

//--------------------------------------------------------------
void BallSystem::setup(int _numOfBalls){

    numOfBalls = _numOfBalls;

    for (int x=0; x<numOfBalls; x++)
    {
        Ball b;
        balls.push_back(b);
    }
}

//--------------------------------------------------------------
void BallSystem::update(){

    for (int x=0; x<balls.size(); x++)
    {
        balls[x].move();
        balls[x].borders();
        balls[x].cure();
    }
    checkInfections();
    removeDeadBalls();
}

//--------------------------------------------------------------
void BallSystem::draw(){
    ofPushStyle();
    for (int x=0; x<balls.size(); x++)
    {
        balls[x].draw();
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void BallSystem::addBall(int x, int y){
    Ball b;
    b.location = ofVec2f(x, y);
    balls.push_back(b);
}

//--------------------------------------------------------------
void BallSystem::infectBall(int mX, int mY){
    for (int x=0; x<balls.size(); x++)
    {
        if (balls[x].isInside(mX, mY)==true)
        {
            balls[x].health=0;
        }
    }
}

//--------------------------------------------------------------
void BallSystem::checkInfections()
{
  for (int i=0; i<balls.size(); i++)
  {
    for (int j=0; j<balls.size(); j++)
    {
        if (i!=j)
        {
            if (balls[i].health<255 || balls[j].health<255) // if one of the two balls is infected
            {
                float b2b_distance = ofDist(balls[i].location.x, balls[i].location.y, balls[j].location.x, balls[j].location.y);  //calculate distance between their centers
                float sumRad = balls[i].radius + balls[j].radius;

                if (b2b_distance < sumRad) // if they are touching infect both
                {
                    balls[i].health = 0;
                    balls[j].health = 0;
                }
            }
        }
    }
  }
}

//--------------------------------------------------------------
void BallSystem::removeDeadBalls()
{
    for (int i=0; i<balls.size(); i++)
    {
        if (balls[i].isAlive==false)
        {
            balls.erase(balls.begin()+i);
        }
    }
}
//---------------------------------------------------------------
vector <ofPoint> BallSystem::getPoints(){
    vector <ofPoint> pts;
    for (int i=0; i<balls.size(); i++) {
        pts.push_back(balls[i].location);
    }
    return pts;
}
//---------------------------------------------------------------
Ball BallSystem::getNearestBall(ofPoint p)
{
    float record = 99999999;
    int recordBallIndex=0;
    for (int i=0; i<balls.size(); i++) {
        float d = ofDistSquared(p.x, p.y, balls[i].location.x, balls[i].location.y);
        if (d<record){
            record = d;
            recordBallIndex = i;
        }
    }
    return balls[recordBallIndex];
}

