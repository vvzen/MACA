#include "ofMain.h"
#include "ofApp.h"

// PHASE 1
// 1. Create a new flow field
// 1.1 A flow field is made by a grid of random vectors
// 1.1.1 The number of cells of the grid is rows * cols
// 1.1.2 Init a random vector in each cell
// 1.1.2.1 A random vector is created using a random angle? and then normalized. theta = arc2( y / x)
// PHASE 2
// 2. Create a boids simulation that leaves painted trails
// 2.1 The boids have a small desire to flow through the Flow Field
// 2.1.1 Desired = steering - velocity
// 2.2 The boids have flocking and steering behaviours
// 2.3 Each boid leaves a coloured trail
// 2.3.1 All of the paint trails should be in a separate fbo

//========================================================================
int main(int argc, char * argv[]){
	ofSetupOpenGL(2560,1440,OF_WINDOW);			// <-------- setup the GL context

    ofApp * myApp = new ofApp();
    
    // Save command line args
    myApp->arguments.resize(0);
    for(int i = 0; i < argc; i++){
        myApp->arguments.push_back(argv[i]);
    }
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
