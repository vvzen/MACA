#include "Superformula.h"
#define POINTNUM 360

Superformula::Superformula(){
    //default values in case setup() is not called.
    scaler = 200;
    m = 2;
    n1 = 18;
    n2 = 1;
    n3 = 1;
    layers = 1;
    shapeColor = ofColor(255);
}
//===============================================================================
void Superformula::update(float _m, float _n1, float _n2, float _n3, int _scaler, int _layers, ofColor _c){
    m = _m;
    n1 = _n1;
    n2 = _n2;
    n3 = _n3;
    scaler = _scaler;
    shapeColor = _c;
    layers = _layers;
}
//===============================================================================
void Superformula::draw(int x, int y){
  ofBackground(0, 0, 0);
  ofPushStyle();
  ofSetColor(shapeColor);
  ofPushMatrix();
  ofTranslate(x, y);

  float newscaler = scaler;
  for(int s = layers; s > 0; s--){ // was layers

    ofBeginShape();

    float mm = m + s;
    float nn1 = n1 + s;
    float nn2 = n2 + s;
    float nn3 = n3 + s;
    newscaler = newscaler * 0.98; //was 0.96
    float sscaler = newscaler;

    ofPoint* points = superformula(mm, nn1, nn2,  nn3);
    ofCurveVertex(points[POINTNUM-1].x * sscaler, points[POINTNUM-1].y * sscaler);
    for(int j = 0; j < POINTNUM; j++){
      ofCurveVertex(points[j].x * sscaler, points[j].y * sscaler);
    }
    ofCurveVertex(points[0].x * sscaler, points[0].y * sscaler);
    ofEndShape(true);
  }
  ofPopStyle();
  ofPopMatrix();
}
//===============================================================================
ofPoint Superformula::superformulaPoint(float m, float n1, float n2, float n3, float phi)
{
  float r;
  float t1,t2;
  float a=1,b=1;
  float x = 0;
  float y = 0;

  t1 = cos(m * phi / 4) / a;
  t1 = fabs(t1);
  t1 = pow(t1,n2);

  t2 = sin(m * phi / 4) / b;
  t2 = fabs(t2);
  t2 = pow(t2,n3);

  r = pow(t1+t2,1/n1);
  if (fabs(r) == 0) {
    x = 0;
    y = 0;
  }
  else {
    r = 1 / r;
    x = r * cos(phi);
    y = r * sin(phi);
  }
  return ofPoint(x, y);
}

//===============================================================================
ofPoint* Superformula::superformula(float m, float n1, float n2, float n3)
{
  int numPoints = POINTNUM;
  float phi = TWO_PI / numPoints;
  ofPoint* retPoints = new ofPoint[numPoints+1];
  for(int i = 0; i <= numPoints; i++){
    retPoints[i] = superformulaPoint(m, n1, n2, n3, phi * i);
  }
  return retPoints;
}
