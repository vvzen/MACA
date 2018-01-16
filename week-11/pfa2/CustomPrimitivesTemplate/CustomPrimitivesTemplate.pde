//////////////////////////////////////
// Custom primitives template
// liorbengai
// Jan 2018
//////////////////////////////////

import peasy.*;

Polymorph shape;
PeasyCam cam;

void setup() {
  size(1280, 800, P3D);
  cam = new PeasyCam(this, 100);
  cam.setMinimumDistance(10);
  cam.setMaximumDistance(1024);
  noiseSeed(12);
  shape = new Polymorph();
}

void draw() {
  background(0);
  drawAxis();
  noFill();
  stroke(255);
  strokeWeight(2);
  shape.update();
  shape.draw();
}


void drawAxis() {
  pushStyle();
  strokeWeight(1);
  // X
  stroke(255, 0, 0);
  line(0, 0, 0, 100, 0, 0);
  // Y
  stroke(0, 255, 0);
  line(0, 0, 0, 0, 100, 0);
  // Z
  stroke(0, 0, 255);
  line(0, 0, 0, 0, 0, 100);
  popStyle();
}
