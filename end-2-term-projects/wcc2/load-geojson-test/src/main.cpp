#include "ofMain.h"
#include "ofApp.h"
#include "globals.h"

//========================================================================
int main( ){
	// ofSetupOpenGL(2560,1080,OF_WINDOW);			// <-------- setup the GL context

	ofGLFWWindowSettings settings;
	// settings.setGLVersion(3, 2);
	settings.width = WIDTH;
	settings.height = HEIGHT;
	// settings.windowMode = OF_FULLSCREEN; // seems to be bugged
	auto window = ofCreateWindow(settings);
	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();
}
