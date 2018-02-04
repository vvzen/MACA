//////////////////////////////////////
// Artifact Lab - wrapper template project for exploring 3D forms
// VERSION 0.2
// liorbengai
// Jan 2018

// 1. GLOBAL VARIABLES
// 2. SETUP AND DRAW
// 3. GUI - SETUP AND DRAW
// 4. GUIDES AND HELPERS
// 5. EVENT HANDLERS
//////////////////////////////////

// Library import
import peasy.*;
import controlP5.*;
//import nervoussystem.obj.*;

// camera and GUI
PeasyCam cam;
ControlP5 cp5;

// GUI vars
Textlabel fpsLbl;
boolean toggle_axis = true, toggle_grid = true, auto_update = false;
float param_A, param_B;
float param_C, param_D;

// scene vars
Artifact shape;
String shapeMode = "tree";

void setup() {
  size(1024, 768, P3D);
  // Setup PeasyCam
  cam = new PeasyCam(this, 100);
  cam.setMinimumDistance(10);
  cam.setMaximumDistance(4000);

  // Setup ControlP5
  setupGUI();

  // setup scene
  shape = new Artifact();
}

void draw() {
  background(0);

  if(toggle_grid)drawGrid();
  if(toggle_axis)drawAxis();

  noFill();
  stroke(255);
  strokeWeight(2);

  shape.update();
  shape.draw(this.g);

  drawGUI();
}

////////////////////////
// SETUP AND DRAW GUI
//////////////////////

// create a list of controlP5 library GUI elements
// See examples folder in processing
void setupGUI(){
  cp5 = new ControlP5(this);
  cp5.setAutoDraw(false);

  // draw current framerate as a label
  fpsLbl = new Textlabel(cp5,"fps",10,10,128,16);

  // on/off toggle buttons
  cp5.addToggle("toggle_grid").setPosition(10,40).setSize(16,16);
  cp5.addToggle("toggle_axis").setPosition(10,80).setSize(16,16);
  cp5.addToggle("auto_update").setPosition(10,120).setSize(16,16);

  // float sliders
  cp5.addSlider("param_A")
     .setId(1)
     .setPosition(10,200)
     .setSize(128,16)
     .setRange(0,256);

  cp5.addSlider("param_B")
      .setId(2)
      .setPosition(10,220)
      .setSize(128,16)
      .setRange(0,256);

  // float sliders
  cp5.addSlider("param_C")
     .setId(3)
     .setPosition(10,240)
     .setSize(128,16)
     .setRange(0,256);

  cp5.addSlider("param_D")
      .setId(4)
      .setPosition(10,260)
      .setSize(128,16)
      .setRange(0,256);

  // buttons
  cp5.addButton("recreate").setPosition(10,300).setSize(64,16);
  cp5.addButton("exportMesh").setPosition(10,320).setSize(64,16);

}

void drawGUI() {
  // do not move the camera while manipulating the gui
  if (cp5.isMouseOver()) {
    cam.setActive(false);
  } else {
    cam.setActive(true);
  }
  // draw the GUI outside of the camera's view
  hint(DISABLE_DEPTH_TEST);
  cam.beginHUD();
  cp5.draw();
  fpsLbl.setValueLabel("fps: " + floor(frameRate));
  fpsLbl.draw(this);
  cam.endHUD();
  hint(ENABLE_DEPTH_TEST);
}

////////////////////////
// GUIDES AND HELPERS
//////////////////////

void drawAxis() {
  pushStyle();
  // X
  strokeWeight(3);
  stroke(255, 0, 0);
  line(0, 0, 0, 100, 0, 0);
  strokeWeight(9);
  point(100, 0, 0);
  // Y
  strokeWeight(3);
  stroke(0, 255, 0);
  line(0, 0, 0, 0, 100, 0);
  strokeWeight(9);
  point(0, 100, 0);
  // Z
  strokeWeight(3);
  stroke(0, 0, 255);
  line(0, 0, 0, 0, 0, 100);
  strokeWeight(9);
  point(0, 0, 100);

  popStyle();
}

void drawGrid() {
  pushStyle();
  pushMatrix();
  strokeWeight(1);
  stroke(180);
  float sz = 100;
  int nm = 8;
  // draw lines along the flat XY plane
  for(int i = 0; i <= nm; i++){
    line( (i * sz) - (sz*nm/2), -sz*nm/2, 0, (i * sz) - (sz*nm/2), sz*nm/2, 0);
    line( -sz*nm/2, (i * sz) - (sz*nm/2), 0, sz*nm/2, (i * sz) - (sz*nm/2), 0);
  }
  popMatrix();
  popStyle();
}

//////////////////////
// GUI EVENT HANDLERS
////////////////////

// empty the shape and recreate its vertices
public void recreate(int theValue) {
  shape.setup(shapeMode);
}

public void exportMesh(int theValue) {
  shape.exportMesh("ArtifactLab_output");
}


// this handler gets called whenever ANY gui element gets changed!

public void controlEvent(ControlEvent theEvent) {

  if(auto_update){
    shape.setup(shapeMode);
  }

  switch(theEvent.getId()) {
    case(1):
      // react to id - 1
    break;
    case(2):
     // react to id - 2
    break;
  }
}

//
