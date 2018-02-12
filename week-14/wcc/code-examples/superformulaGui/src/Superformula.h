#include "ofMain.h"

class Superformula {

  public:
    Superformula();
    void draw(int x, int y);
    void update(float _m, float _n1, float _n2, float _n3, int _scaler, int _layers, ofColor _c);
    ofPoint* superformula(float m, float n1, float n2, float n3);
    ofPoint superformulaPoint(float m, float n1, float n2, float n3, float phi);

    float scaler;
    int m, layers;
    float n1, n2, n3;
    ofColor shapeColor;
};
