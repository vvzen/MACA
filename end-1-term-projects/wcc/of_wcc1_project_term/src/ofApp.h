#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "BouncingBallsSource.h"
#include "MovingRectSource.h"
#include "VideoSource.h"
#include "SceneManager.h"

#include "MovementISource.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
		void keyReleased(int key);
	
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);

		ofxPiMapper piMapper;

		// By using a custom source that is derived from FboSource
		// you will be able to see the source listed in sources editor
        BouncingBallsSource * bouncingBallsSource;
        MovingRectSource * movingRectSource;
        ofImage dummyObjects;

        MovementISource * movementISource;

        SceneManager sceneManager;
};
