#include "LinesSource.h"

void LinesSource::setup(){
	
    // no need to give a name here since we're naming it in the ofApp
    // Give our source a decent name
	//name = "Custom FBO Source";

	// Allocate our FBO source, decide how big it should be
	allocate(512, 512);
    
    // resolution of line (as number of points)
    // lower numbers mean higher
    int x_step = 2;
    // distance between lines
    int y_step = 10;
    
    // create the lines and the points
    for (int y = 0; y < fbo->getHeight(); y += y_step){
        
        // create a new line
        Line line;
        vector <ofPoint *> points;
        ofColor line_color;
        
        // create the relative points
        for (int x = 0; x <= fbo->getWidth() + 20; x+= x_step){
            
            ofPoint * current_point = new ofPoint(x, y);
            points.push_back(current_point);
        }
        // set the color of the line
        line_color.setHsb(ofMap(y, 0, fbo->getHeight(), 100, 140), 255, 255);
        line.setup(points, line_color);
        
        lines.push_back(line);
    }
}

void LinesSource::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void LinesSource::update(){
	
    // move displacing agents
    
    // REPULSION
    float f_angle = ofGetElapsedTimeMillis() * 0.01;
    float f_radius_multiplier = ofNoise(ofGetElapsedTimeMillis() * 0.002) * ofRandom(-1, 1);
    
    fear.x = f_radius_multiplier * fbo->getWidth() * sin(f_angle * 0.3) + fbo->getWidth()/2;
    fear.y = f_radius_multiplier * fbo->getHeight() * cos(f_angle * 0.1) + fbo->getHeight()/2;
    
    // ATTRACTION
    float a_angle = ofGetElapsedTimeMillis();
    float a_radius_multiplier = ofNoise(ofGetElapsedTimeMillis() * 0.001);
    
    attraction.x = a_radius_multiplier * fbo->getWidth() * sin(a_angle * 0.0016) + fbo->getWidth()/2;
    attraction.y = a_radius_multiplier * fbo->getHeight() * cos(a_angle * 0.002) + fbo->getHeight()/2;
    
    for (int l = 0; l < lines.size(); l++){
        
        lines.at(l).displace(fear, DISTANCE_THRESHOLD * 4, true);
        //lines.at(l).displace(attraction, DISTANCE_THRESHOLD * 3, false);
        
        lines.at(l).update();
    }
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void LinesSource::draw(){
    
    ofClear(0);
    ofEnableSmoothing();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    // visualize agents
    if (DEBUG) {
        ofSetColor(0,0,255);
        ofDrawCircle(fear.x, fear.y, 5);
        ofSetColor(255,0,0);
        ofDrawCircle(attraction.x, attraction.y, 5);
    }
    
    ofSetLineWidth(2);
    
    // draw lines
    for (int i = 0; i < lines.size(); i++){
        
        lines.at(i).draw();
    }
}
