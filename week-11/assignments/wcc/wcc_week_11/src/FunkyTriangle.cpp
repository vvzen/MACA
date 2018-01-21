#include "FunkyTriangle.h"

//--------------------------------------------------------------
void FunkyTriangle::setup(ofPoint p1, ofPoint p2, ofPoint p3, float hue){

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    color = ofColor(0);
    color.setHsb(hue, 204, 190);
    // color_seed = ofRandom(0, 1000);
    color_seed = ofRandom(-28, 28);
    color_hue = color.getHue();
    color.setHue(color_hue + color_seed);
}

//--------------------------------------------------------------
void FunkyTriangle::update(){

    color.setHue(color_hue);
    float sat = ofMap(sin((ofGetElapsedTimef() + color_seed) * 1.24f), -1, 1, 40, 240);
    color.setSaturation(sat);

    // slowly shift hue
    if (color_hue > 255.0f){
        color_hue = 0.0f;
    }
    color_hue += 0.22f;
}

//--------------------------------------------------------------
void FunkyTriangle::draw(){
    
    ofPushMatrix();

    ofPushStyle();

    ofSetColor(color);
    
    // ofDrawTriangle(points[0], points[1], points[2]);

    // ofSetColor(255, 255, 255);
    // ofDrawCircle(points[0].x, points[0].y, 4, 4);
    // ofDrawCircle(points[1].x, points[1].y, 4, 4);
    // ofDrawCircle(points[2].x, points[2].y, 4, 4);
    
    // find the center of the 3 given points
    ofPoint center;
    center.x = (points[0].x + points[1].x + points[2].x) / 3.0f;
    center.y = (points[0].y + points[1].y + points[2].y) / 3.0f;

    ofSetColor(0, 255, 0);
    ofTranslate(center.x, center.y, 0);
    // ofDrawCircle(0, 0, 2, 2);
    
    // recompute position of points from their center
    ofPoint p1 = ofPoint(points[0].x - center.x, points[0].y - center.y);
    ofPoint p2 = ofPoint(points[1].x - center.x, points[1].y - center.y);
    ofPoint p3 = ofPoint(points[2].x - center.x, points[2].y - center.y);
    
    // draw triangles shrinking them towards the center
    float minimum = 0.0f;
    float maximum = 3.0f;
    for (float i = minimum; i <= maximum; i+=0.25f){
        
        float scale_factor = ofMap(i, minimum, maximum, 1.0f, 0.02f);
        float rotate_factor = ofMap(i, minimum, maximum, 0.0f, 3.0f);
        ofScale(scale_factor, scale_factor, 1);
        ofRotateZ(rotate_factor);

        ofColor current_color = color;        
        current_color.setBrightness(ofMap(i, minimum, maximum, color.getBrightness(), 255));
        
        ofSetColor(current_color);
        ofDrawTriangle(p1, p2, p3);
    }

    ofPopStyle();

    ofPopMatrix();
}