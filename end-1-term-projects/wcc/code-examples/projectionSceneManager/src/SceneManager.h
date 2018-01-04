#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxPiMapper.h"

class SceneManager {
	public:
        void setup(string scenesFile, ofxPiMapper *_piMapper);
        void update();
        ofxJSONElement result;
        bool managePresets();
        ofxPiMapper *piMapper;
        int sceneIndex;
        int currentPreset;
        int sceneDuration;
        int totalDuration;
        bool allowTransitions;
};
