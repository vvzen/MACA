//
//  Line.h
//  wcc_lines_test
//
//  Created by Valerio Viperino on 03/12/17.
//
//

#ifndef Line_h
#define Line_h

#include "ofMain.h"
#include <stdio.h>

#define DEBUG 0
#define AWAY_PUSH 0.5 

class Line {
    
    public:
    
        void setup(vector <ofPoint *> _points, ofColor color);
        void displace(ofPoint target, int distance_thresh, bool attract);
        void update();
        void draw();
    
        vector <ofPoint *> points;
    
        ofPolyline polyline;
        ofMesh polymesh;
        ofColor color;
};

#endif /* Line_h */
