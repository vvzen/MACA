#pragma once
#include "ofMain.h"
#include "Ball.h"

class BallSystem{

	public:
	    BallSystem();
	    void setup(int _numOfBalls);
	    void update();
	    void draw();
        void addBall(int x, int y);
        void infectBall(int mX, int mY);
        void removeDeadBalls();
        void checkInfections();
        vector<Ball> balls;
		int numOfBalls;
        vector <ofPoint> getPoints();
        Ball getNearestBall(ofPoint p);
};
