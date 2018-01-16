//////////////////////////////////////
// Polymorph class
// liorbengai
// Jan 2018
//////////////////////////////////

// This class is designed to manage a compound 3D shape.
// you can use the built in functions to create a plane or a sphere structure
// BUT more importantly - Add more functions to it! (i.e: cube, cone, etc)

class Polymorph{

  ArrayList<Vert> vertices;
  PVector position;

  Polymorph(){
    // set initial position to 0;
    position = new PVector(0,0,0);

    //setupSphere(64, 32, 256.0);
    //setupPlane(128, 128, 10.0);
    setupTorus(10, 50, 64, 32);
  }


  void setupPlane(int w, int h, float spacing){
    // Populate the system with a grid of instances of class Agent
    vertices = new ArrayList<Vert>();
    for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
        vertices.add(new Vert(i*spacing - (w*spacing/2.0), j*spacing - (h*spacing/2.0), 0));
      }
    }
  }


  void setupSphere(int resW, int resH, float radius){
    vertices = new ArrayList<Vert>();
    for(float phi = 0.0; phi <= PI; phi += PI/resW) {
      for(float theta = 0.0; theta <= TWO_PI; theta += 1/(resH*sin(phi))) {

        float x = radius * sin(phi) * cos(theta);
        float y = -radius * cos(phi);
        float z = radius * sin(phi) * sin(theta);
        vertices.add(new Vert(x,y,z));
      }
    }
  }


  // my custom function
  void setupTorus(float section, float radius, int resW, int resH){

    vertices = new ArrayList<Vert>();

    // I'm gonna try to build a torus just by having multiple
    // circles going around a center point

    for(float phi = 0.0; phi <= PI; phi += PI/resW) {
      for(float theta = 0.0; theta <= TWO_PI; theta += 1/(resH*sin(phi))) {

        float x = (radius + section * cos(theta)) * cos(phi);  
        float y = (radius + section * cos(theta)) * sin(phi);
        float z = section * sin(theta);

        vertices.add(new Vert(x, y, z));
      }
    }

  }

  void update() {
    // update vertices
    for(int i = 0; i < vertices.size();i++){
      vertices.get(i).update();
    }
  }

  void draw(){
    pushMatrix();
    translate(position.x, position.y, position.z);
    beginShape(POINTS);
    for(int i = 0; i < vertices.size();i++){
      PVector p = vertices.get(i).position;
      vertex(p.x, p.y, p.z);
    }
    endShape();
    popMatrix();
  }

} // class Polymorph
