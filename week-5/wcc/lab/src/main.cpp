#include "ofApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){

	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
    ofSetupOpenGL(900, 400, OF_WINDOW);
	ofRunApp(new ofApp()); // start the app
}
