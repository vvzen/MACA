#include "SandLine.h"

//--------------------------------------------------------------
void SandLine::setup(float w, float h, float max_size, float max_alpha){

    fbo.allocate(w, h, GL_RGBA, 8);

    _max_size = max_size;
    _max_alpha = max_alpha;
    _enable_draw = false;
    points_added = 0;
    
    // initial cleaning of the fbo
    fbo.begin();
    
    ofClear(0);
    ofBackground(0);

    fbo.end();
}

//--------------------------------------------------------------
void SandLine::update(){

    fbo.begin();

    // only draw after we added a point
    if (_enable_draw){
        ofPushStyle();
        for (int i = 0; i < sand_grains.size(); i++){
            ofSetColor(sand_grains.at(i).col);
            ofDrawCircle(sand_grains.at(i).pos.x, sand_grains.at(i).pos.y, sand_grains.at(i).size);
        }
        ofPopStyle();
    }

    fbo.end();

    _enable_draw = false;
}

//--------------------------------------------------------------
void SandLine::add_point(ofVec3f p){

    _enable_draw = true;

    // we need at least one point before drawing a line!
    if (main_sand_points.size() < 1){
        // increase counter for the amount of added points
        points_added++;
        // add the first point
        main_sand_points.push_back(p);
    }
    else {
        
        // increase counter for the amount of added points
        points_added++;

        // add the new point
        main_sand_points.push_back(p);

        // clear the previously generated grains
        sand_grains.clear();

        // cout << "main_sand_points.size(): " << main_sand_points.size() << endl;

        float radius = ofRandom(32, 64);
        float angle = ofMap(ofRandomf(), 0, 1, -PI*2, PI*2);

        // create a bezier curve using randomly generated handles
        ofPoint start_p = main_sand_points.at(0);
        ofPoint anchor_1 = ofPoint(cos(angle) * radius, sin(angle) * radius);
        anchor_1 += start_p;
        ofPoint end_p = main_sand_points.at(1);
        ofPoint anchor_2 = ofPoint(cos(angle) * radius, sin(angle) * radius);
        anchor_2 += end_p;

        // remove the first element, we don't need it anymore
        main_sand_points.pop_front();

        // TODO: create a NICE LOOKING spline between the previous and the current point

        // create the bezier curve
        ofPolyline bezier;
        bezier.addVertex(start_p);
        bezier.bezierTo(anchor_1, anchor_2, end_p);

        // now populate all the bezier path with points
        // those points have a gaussian distribution in order to make them a bit nicer
        // the standard deviation is randomised so we got more variety in the guassian curve shape
        float center_value = 0;
        float stdev = ofRandom(0.035, 0.115);
        float max_offset = 32;

        for (float f = 0; f < 1.0f; f+=0.005){
            for (int i = 0; i < 8; i++){

                std::normal_distribution<double> gaussian_distribution(center_value, stdev);

                ofPoint mid_point = bezier.getPointAtPercent(f);
                mid_point.x += gaussian_distribution(generator) * max_offset;
                mid_point.y += gaussian_distribution(generator) * max_offset;
                Grain grain;
                grain.pos = mid_point;
                grain.col = ofColor(255, ofRandom(_max_alpha));
                grain.size = ofRandom(_max_size);
                sand_grains.push_back(grain);
            }
        }
    }
}

//--------------------------------------------------------------
ofFbo * SandLine::get_fbo_pointer(){
    return &fbo;
}

//--------------------------------------------------------------
void SandLine::enable_draw(bool val){
    _enable_draw = val;
}
