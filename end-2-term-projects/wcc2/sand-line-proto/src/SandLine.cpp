#include "SandLine.h"

//--------------------------------------------------------------
void SandLine::setup(float w, float h, float max_size, float max_alpha, int mode){

    fbo.allocate(w, h, GL_RGBA, 8);

    _max_size = max_size;
    _max_alpha = max_alpha;
    current_mode = mode;

    _enable_draw = false;
    points_added = 0;
    _max_offset = 32;
    
    // used in attractor mode
    acceleration = ofVec2f(0.0f, 0.0f);
    velocity = ofVec2f(0.0f, 0.0f);
    position = ofVec2f(0.0f, 0.0f);

    // initial cleaning of the fbo
    fbo.begin();
    
    ofClear(255);
    ofBackground(255);

    fbo.end();
}

//--------------------------------------------------------------
void SandLine::update(){

    fbo.begin();

    // creates a series of bezier with random handles 
    // passing to the given points (see add_point())
    if (current_mode == BEZIER_MODE){

        ofPushStyle();

        // only draw after we added a point
        if (_enable_draw){
            for (int i = 0; i < sand_grains.size(); i++){
                ofSetColor(sand_grains.at(i).col);
                ofDrawCircle(sand_grains.at(i).pos.x, sand_grains.at(i).pos.y, sand_grains.at(i).size);
            }
        }

        ofPopStyle();
    }
    // feel the attraction toward the latest target set
    // leaves a trail of dots in this eternal search
    else if (current_mode == ATTRACTOR_MODE){

        ofPushStyle();

        ofVec2f attraction_force = latest_target - position;
        // this.acc = p5.Vector.sub(target, this.pos);
        attraction_force.normalize();
        attraction_force += ofVec2f(ofRandom(-0.75f, 0.75f), ofRandom(-0.75f, 0.75f));
        
        float distance = ofDist(latest_target.x, latest_target.y, position.x, position.y);
        distance = ofClamp(distance, 1, 32); // avoids crazy spinning

        float mass = 0.5f;
        // float attraction_factor = ofMap(distance, 0, dist(fbo.getWidth()/2, fbo.getHeight()/2, fbo.getWidth(), fbo.getHeight())), 0, 0.4);
        attraction_force *= mass / distance * distance;
        acceleration += attraction_force;
        velocity += acceleration;
        velocity.limit(8.0);
        position += velocity;

        // those trail of points have a gaussian distribution around the current position
        // the standard deviation (basically the spread of the "brush") follows a 1d noise over time
        float center_value = 0;
        float stdev = ofMap(ofNoise(ofGetElapsedTimef() * 0.8), 0, 1, 0.000035, 0.12);

        for (int i = 0; i < 32; i++){

            float size = ofRandom(_max_size);
            float alpha = ofRandom(_max_alpha);
            
            std::normal_distribution<double> gaussian_distribution(center_value, stdev);
            
            ofVec2f offset = position;
            offset.x += gaussian_distribution(generator) * _max_offset;
            offset.y += gaussian_distribution(generator) * _max_offset;

            ofSetColor(255, alpha);
            ofDrawCircle(offset.x, offset.y, size, size);
        }

        // reset everything
        acceleration = ofVec2f(0, 0);

        ofPopStyle();
    }

    fbo.end();

    _enable_draw = false;
}

//--------------------------------------------------------------
void SandLine::add_point(ofPoint p){

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

        cout << "main_sand_points.size(): " << main_sand_points.size() << endl;

        float radius = ofRandom(32, 64);
        float angle = ofMap(ofRandomf(), 0, 1, -PI*2, PI*2);

        // create a bezier curve using randomly generated handles
        ofPoint start_p = main_sand_points.at(0);
        ofPoint anchor_1 = ofPoint(cos(angle) * radius, sin(angle) * radius);
        anchor_1 += start_p;
        ofPoint end_p = main_sand_points.at(1);
        ofPoint anchor_2 = ofPoint(cos(angle) * radius, sin(angle) * radius);
        anchor_2 += end_p;

        // when we switch to attractor mode the latest target
        // should be following the latest added point
        latest_target = end_p;
        position = start_p;

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

        for (float f = 0; f < 1.0f; f+=0.005){
            for (int i = 0; i < 8; i++){

                std::normal_distribution<double> gaussian_distribution(center_value, stdev);

                ofPoint mid_point = bezier.getPointAtPercent(f);
                mid_point.x += gaussian_distribution(generator) * _max_offset;
                mid_point.y += gaussian_distribution(generator) * _max_offset;
                Grain grain;
                grain.pos = mid_point;
                grain.col = ofColor(0, ofRandom(_max_alpha));
                grain.size = ofRandom(_max_size);
                sand_grains.push_back(grain);
            }
        }
    }
}

//--------------------------------------------------------------
void SandLine::set_target(ofVec2f target){
    latest_target = target;
}

//--------------------------------------------------------------
void SandLine::set_mode(int mode){
    cout << "mode: " << mode << endl;
    current_mode = mode;
}

//--------------------------------------------------------------
ofFbo * SandLine::get_fbo_pointer(){
    return &fbo;
}

//--------------------------------------------------------------
void SandLine::enable_draw(bool val){
    _enable_draw = val;
}
