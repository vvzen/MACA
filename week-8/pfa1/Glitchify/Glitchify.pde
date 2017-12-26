//////////////////////
// Glitchify.pde   //
// liorbengai     //
// November 2017 //
//////////////////

import controlP5.*;
ControlP5 cp5;

PImage original; // A container for an image to load
PImage glitched; // A copy to mess with
boolean hasImage = false;
boolean applyEffect = false;

void setup(){
  size(1280,800);
  smooth(0);
  setupGUI();
}

void draw(){
  background(32);

  if(hasImage){
    if(applyEffect){
      // create 3 parameters for the effect to use
      int segLength = floor(random(20, 200));
      int sourceIndex = floor(random(0, glitched.pixels.length - segLength ));
      int destinationIndex = floor(random(0, glitched.pixels.length - segLength ));

      glitched.loadPixels();

      for(int i = 0; i < segLength ; i++){
          // take the value of a source pixel and put it in dest
          color c = glitched.pixels[ sourceIndex + i ];
          glitched.pixels[ destinationIndex + i ] = c;
      }
      
      glitched.updatePixels();
    }
    // draw the glitched image at the center of the screen
    pushMatrix();
    translate(width/2, height/2);
    image(glitched, - glitched.width/2 ,  - glitched.height/2);
    popMatrix();
  }
}

// setup ControlP5 and create the buttons
void setupGUI(){
  cp5 = new ControlP5(this);

  cp5.addButton("Import")
     .setPosition(32,32)
     .setSize(128,32)
     ;

  cp5.addToggle("toggleGlitch")
    .setPosition(32,96)
    .setSize(128,32)
    .setValue(false)
    .setMode(ControlP5.SWITCH)
    ;

  cp5.addButton("ResetImage")
    .setPosition(32,96 + 64)
    .setSize(128,32)
    ;

  cp5.addButton("Export")
    .setPosition(32,96 + 128)
    .setSize(128,32)
    ;
}

// show the file browser
public void Import(int theValue) {
    selectInput("Select a file to process:", "fileSelected");
}
// user has selected a file (or not)
void fileSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    original = loadImage(selection.getAbsolutePath());
    glitched = loadImage(selection.getAbsolutePath());
    hasImage = true;
  }
}

// toggle the flag that controls the effect
void toggleGlitch(boolean theFlag) {
  applyEffect = theFlag;
}

// reset to a fresh copy of the image
public void ResetImage(int theValue) {
  glitched = original.copy();
}

// save the result to the project folder
public void Export(int theValue) {
  glitched.save("output.png");
}
