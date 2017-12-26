//////////////////////////////////////
// Empty_3D.pde                    //
// A template for 3D projects     //
// in processing using PeasyCam  //
// liorbengai                   //
// December 2017               //
////////////////////////////////


import peasy.*;
PeasyCam cam;

void setup() {
  size(1280,800,P3D); // use the P3D renderer
  cam = new PeasyCam(this, 2000); // instantiate PeasyCam, initial distance of 2000 units
  cam.setMinimumDistance(0); // close clipping plane
  cam.setMaximumDistance(5000); // far clipping plane

  // CUSTOM SETUP CODE:

}

void draw() {
  background(127); // always redraw
  drawGrid(20, 20, 100);
  drawAxis();

  // CUSTOM DRAW CODE:

}

void drawAxis(){
  pushStyle();
  strokeWeight(3);
  float sz = 300;
  // draw the lines
  stroke(255,0,0); // R
  line(0,0,0,sz,0,0); // X
  stroke(0,255,0); // G
  line(0,0,0,0,sz,0); // Y
  stroke(0,0,255); //B
  line(0,0,0,0,0,sz); // Z

  // draw the tips
  strokeWeight(12);
  stroke(255,0,0); // R
  point(sz,0,0); // X
  stroke(0,255,0); // G
  point(0,sz,0); // Y
  stroke(0,0,255); //B
  point(0,0,sz); // Z

  popStyle();
}


// draw a grid with variable width height and size
void drawGrid(int rows, int cols, float sz ){
  pushMatrix();
  pushStyle();
  stroke(255);
  // move to negative edge of the grid
  translate(-rows*0.5*sz,-cols*0.5*sz );

  // draw the rows
  for(int i = 0; i < rows+1; i++){
    line(i *sz, 0 ,i*sz, cols*sz);
  }
  // draw the columns
  for(int j = 0; j < cols+1; j++){
    line(0,j *sz, rows*sz ,j*sz);
  }

  popStyle();
  popMatrix();
}






// END
