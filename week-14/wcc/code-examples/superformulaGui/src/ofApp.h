#include "ofMain.h"
#include "Superformula.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

  public:
    void setup();
    void draw();
    void update();

    Superformula superformula;

    ofxIntSlider m, scaler, layers;
    ofxFloatSlider n1, n2, n3;
    ofxColorSlider formulaColor;

	ofxPanel gui;
};
