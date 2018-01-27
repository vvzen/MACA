#include "Snake.h"

void Snake::setup(ofColor c){
    target_c = c;
}

void Snake::addLocation(int x, int y){

    ofPoint point(x, y);
    snakePoints.push_front(point);

    if (snakePoints.size() > 50){
        snakePoints.pop_back();
    }
}

void Snake::draw(){

    float currentShortestDistance = 100;

    ofPushStyle();

    // for (int i = 0; i < snakePoints.size(); i++){
    //     ofDrawCircle(snakePoints[i].x, snakePoints[i].y, 5, 5);
    // }

    for (int i = 0; i < snakePoints.size(); i++){
        for (int j = 0; j < snakePoints.size(); j++){
            
            ofSetColor(255, ofMap(i, 0, snakePoints.size(), 255, 0));

            float currentDistance = ofDist(snakePoints[i].x, snakePoints[i].y, snakePoints[j].x, snakePoints[j].y);

            if (currentDistance < 20){
                // currentShortestDistance = currentDistance;
                ofDrawLine(snakePoints[i].x, snakePoints[i].y, snakePoints[j].x, snakePoints[j].y);
            }
        }
    }

    ofPopStyle();

}