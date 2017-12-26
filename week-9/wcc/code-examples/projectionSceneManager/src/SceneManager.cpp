#include "SceneManager.h"
//note: I could refactor in order to get rid of some of the repetition between the two functions

void SceneManager::setup(string scenesFile, ofxPiMapper *_piMapper){
    piMapper = _piMapper;
    if (result.open(scenesFile)){
        cout << "file opened successfully" << endl;
        allowTransitions = true;
    }
    else {
        cout << "scene file " << scenesFile << " not found" << endl;
        allowTransitions = false;
    }
    sceneIndex = 0;
    currentPreset = result[sceneIndex]["preset"].asInt();
    sceneDuration = result[sceneIndex]["duration"].asInt();

    if (sceneDuration<=0) {
        allowTransitions = false;
        cout << "scene duration set to <= 0, therefore transitions turned off." << endl;
    }
}

// Don't do any drawing here
void SceneManager::update(){
    if (ofGetElapsedTimeMillis()>sceneDuration && allowTransitions) {
        sceneIndex++;
        if (sceneIndex >= result.size()) {
            cout << "Warning: end of scenes reached. Restarting from 0." << endl;
            sceneIndex = 0;
        }

        int targetPreset = result[sceneIndex]["preset"].asInt();

        if (targetPreset>=piMapper->getNumPresets()){
            cout << "ERROR: skipping scene " << sceneIndex << " as preset " << targetPreset << " does not exist" << endl;
        }
        else {
            piMapper->setPreset(targetPreset);
            int tempDuration = result[sceneIndex]["duration"].asInt();
            if (tempDuration<=0){
                allowTransitions = false;
                cout << "scene duration set to <= 0, therefore transitions turned off." << endl;
                return;
            }
            sceneDuration+=tempDuration;
            cout << sceneIndex << " changed to " << piMapper->getActivePresetIndex() << " for " << sceneDuration << endl;
        }
    }
}
