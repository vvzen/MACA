//
//  Line.cpp
//  wcc_lines_test
//
//  Created by Valerio Viperino on 03/12/17.
//
//

#include "Line.h"

// pass the points as a pointer
void Line::setup(vector <ofPoint *> _points, ofColor _color){
    
    points = _points;
    color = _color;
    
    polymesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    
    for (int i = 0; i < points.size(); i++){
        
        //ofPoint * current_point = points.at(i);
        //polymesh.addVertex(ofPoint(points[i]->x, points[i]->y));
        
        polyline.curveTo(ofPoint(points[i]->x, points[i]->y));
    }
}

void Line::displace(ofPoint target, int distance_threshold, bool attract){
    
    for (int i = 0; i < points.size(); i++){
        
        ofPoint * current_point = points.at(i);
        
        float distance = ofDist(current_point->x, current_point->y, target.x, target.y);
        
        float force_push = ofMap(distance, 0, distance_threshold, 1, 0.01);
        
        //cout << "distance threshold: " << distance_threshold << endl;
        //cout << "distance : " << distance << endl;
        
        // skip first and last point
        if (i > 1 || i < points.size()-1){
        
            if (distance < distance_threshold){
                
                ofVec2f force;
                if (attract){
                    // create vector pointing away target
                    force = *current_point - target;
                }
                else {
                    // create vector pointing towards target
                    force = target - *current_point;
                }
                
                force.normalize();
                force *= pow(force_push, 2);
                //force *= force_push * 2;
                
                points[i]->x += force.x;
                points[i]->y += force.y;
            }
            
        }
    }
}

void Line::update(){
    
    // clear previous line
    polyline.clear();
    
    //polymesh.clear();
    
    for (int i = 0; i < points.size(); i++){
        // mesh
        //polymesh.addVertex(ofPoint(points[i]->x, points[i]->y));
        //polymesh.addIndex(i);
        //polymesh.addColor(color);
        
        polyline.curveTo(ofPoint(points[i]->x, points[i]->y));
    }
}


// RENDERING
void Line::draw(){
    
//    if (DEBUG){
//        for (int i = 0; i < points.size(); i++){
//            
//            ofDrawCircle(points[i]->x, points[i]->y, 3);
//        }
//    }
    
    ofSetColor(color);
    polyline.draw();
    //polymesh.draw();
}