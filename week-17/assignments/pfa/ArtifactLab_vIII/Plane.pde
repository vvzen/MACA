////////////////////////////////////////////////////////////////////////
// Plane class
// liorbengai
// Jan 2018

// This class extends the Artifact class to create a custom plane
// you can modify or extend it to create other 3D structures

// 1. PROPERTIES
// 2. CONSTRUCTOR
// 3. METHODS
//  * setup
//  * draw
////////////////////////////////////////////////////////////////////////
public class Plane extends Artifact{

  // PROPERTIES
  int wid;
  int hei;
  float scl;

  // CONSTRUCTOR
  Plane(){
    super();
  }

  // SETUP
  // override setup function to create a plane
  public void setup(){
    vertices = new ArrayList<Vert>();
    wid = 128;
    hei = 128;
    scl = 10;
    for(int i = 0; i < wid; i++){
      for(int j = 0; j < hei; j++){
        pushVert(i*scl - (wid*scl/2.0),
                 j*scl - (hei*scl/2.0),
                 0);
      }
    }
  }

  // DRAW
  // override draw function to draw a plane
  public void draw(PGraphics pg){

    pushTransform(pg);

    // draw vertices on plane with triangles
    for(int i = 0; i < wid -1;i++){
      pg.beginShape(TRIANGLE_STRIP);
      for(int j = 0; j < hei ;j++){

        PVector p = vertices.get( (i * wid) + j ).position;
        PVector p2 = vertices.get( ((i+1) * hei) + j).position;

        pg.vertex(p.x, p.y, p.z);
        pg.vertex(p2.x, p2.y, p2.z);
      }
      pg.endShape();
    }
    popTransform(pg);
  }
} // END class Plane








//
