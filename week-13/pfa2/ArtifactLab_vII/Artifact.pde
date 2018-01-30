////////////////////////////////////////////////////////////////////////
// Artifact
// liorbengai
// Jan 2018

// This class is designed to manage a compound 3D shape.
// you can use the built in functions to create custom shape structures
// BUT more importantly - Add new functions to it!

// 1. PROPERTIES (variables)
// 2. CLASS SETUP
// 3. UPDATE
// 4. DRAW
// 5. SHAPE CREATION METHODS
// 6. HELPERS / EQUATION METHODS
////////////////////////////////////////////////////////////////////


class Artifact{

  ////////////////////////
  // CLASS PROPERTIES
  //////////////////////
  ArrayList<Vert> vertices;
  PVector position;
  PVector rotation;
  PVector scale;
  String mode = "";

  ////////////////////////
  // SETUP SHAPE
  //////////////////////
  Artifact(){
    // set initial transformtaions
    position = new PVector(0,0,0);
    rotation = new PVector(0,0,0);
    scale = new PVector(1.,1.,1.);
    vertices = new ArrayList<Vert>();
  }

  void setup(String _mode){
    mode = _mode;
    // create/empty the arrayList
    vertices = new ArrayList<Vert>();

    if(mode == "plane"){
      setupPlane(128, 128, 10.0); // width, height, spacing
    }else if(mode == "sphere"){
      setupSphere(32, 64, 512); // resolution width, resolution height, radius
    }else if(mode == "cube"){
      setupCube( 32,32,32, 8); // width, height, depth, spacing
    }

  }


  ////////////////////////
  // UPDATE VERTICES
  //////////////////////
  void update() {
    // update all vertices
    if(mode != ""){
      for(int i = 0; i < vertices.size();i++){
        vertices.get(i).update();
      }
    }
  }

  ////////////////////////
  // DRAW A SHAPE
  //////////////////////
  // draws a shape to a given PGraphics object
  void draw(PGraphics pg){
    // transformations
    pg.pushMatrix();
    pg.translate(position.x, position.y, position.z);
    pg.rotateX(rotation.x);
    pg.rotateY(rotation.y);
    pg.rotateZ(rotation.z);
    pg.scale(scale.x, scale.y, scale.z);

    //draw all vertices as points
    pg.beginShape(POINTS);
    for(int i = 0; i < vertices.size();i++){
      PVector p = vertices.get(i).position;
      pg.vertex(p.x, p.y, p.z);
    }
    pg.endShape();


    pg.popMatrix();
  }


  ////////////////////////////////////////
  // CREATE VERTICES AS CUSTOM 3D SHAPES
  //////////////////////////////////////

  // create a flat plane of vertices
  void setupPlane(int w, int h, float spacing){
    for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
        pushVert(i*spacing - (w*spacing/2.0),
                 j*spacing - (h*spacing/2.0),
                 0);
      }
    }
  }

  // create a sphere of vertices
  void setupSphere(int resW, int resH, float radius){

    for(float phi = 0.0; phi <= PI; phi += PI/resW) {
      for(float theta = 0.0; theta <= TWO_PI; theta += 1/(resH*sin(phi))) {

        float x = radius * sin(phi) * cos(theta);
        float y = radius * sin(phi) * sin(theta);
        float z = -radius * cos(phi);
        pushVert(x,y,z);
      }
    }
  }


  // create a cube of vertices
  void setupCube(int w, int h, int d, float spacing ){

    for(int k = 0; k < d; k++){
      for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            pushVert(i*spacing - (w*spacing/2.0),
                     j*spacing - (h*spacing/2.0),
                     k*spacing - (w*spacing/2.0));
        }
      }
    }
  }

  // create a hollow cube - with just the six sides
  void setupHollowCube(int w, int h, int d, float spacing ){
    for(int k = 0; k < d; k++){
      for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){

          boolean edge = (k == 0 || k == d-1) ||
                         (i == 0 || i == w-1) ||
                         (j == 0 || j == h-1);
          if(edge){
            pushVert(i*spacing - (w*spacing/2.0),
                     j*spacing - (h*spacing/2.0),
                     k*spacing - (w*spacing/2.0));
          }
        }
      }
    }
  }

  void setupSuperFormula(){

    float step = 0.1;
    float n1 = random(0.8,20.0);
    float n2 = random(0.8,2.0);
    float n3 = random(0.8,2.0);
    float n4 = random(0.8,2.0);
    float a1 = random(0.8,4.0);
    float a2 = random(0.8,8.0);

    int N_X = ceil((2.0*PI) / step);
    int N_Y = ceil(PI / step);

    for(int x=0;x<N_X;x++) {
        for(int y=0;y<N_Y;y++) {
            pushVert(sf3d(x, y, step, n1, n2, n3, n4, a1, a2));
        }
    }
  }


  ////////////////////////////////////////
  // MESH EXPORT
  //////////////////////////////////////

  // This uses the OBJExport library:
  // https://n-e-r-v-o-u-s.com/tools/obj/
  void exportMesh(String fileName){
    //export an x3d file, change to OBJExport for obj
    // MeshExport output = (MeshExport) createGraphics(10, 10, "nervoussystem.obj.X3DExport", fileName + ".x3d");
    // output.beginDraw();
    // this.draw(output);
    // output.endDraw();
    // output.dispose();
    // println(fileName + " Export complete.");
  }
  

  ////////////////////////
  // HELPERS / EQUATIONS
  //////////////////////

  // Helper functions to create and add new vert classes to the arraylist
  // Version A - vector
  void pushVert(PVector v){
    vertices.add(new Vert(v.x,v.y,v.z));
  }
  // Version B - 3 floats
  void pushVert(float x, float y, float z){
    vertices.add(new Vert(x,y,z));
  }

  // for the following parameters - return a single 3D position
  // mapped using the superformula:
  // https://en.wikipedia.org/wiki/Superformula
  PVector sf3d(float x, float y, float step,
               float n1, float n2, float n3, float n4,
               float a1, float a2){

      float i = -PI + x*step;
      float j = -PI/2.0 + y*step;

      float raux1 = pow(abs(1/a1*abs(cos(n1 * i/4))),n3)+pow(abs(1/a2*abs(sin(n1*i/4))),n4);
      float r1=pow(abs(raux1),(-1/n2));

      float raux2=pow(abs(1/a1*abs(cos(n1*j/4))),n3)+pow(abs(1/a2*abs(sin(n1*j/4))),n4);
      float r2=pow(abs(raux2),(-1/n2));

      PVector res = new PVector(r1*cos(i)*r2*cos(j)*100.0f
                               ,r1*sin(i)*r2*cos(j)*100.0f
                               ,r2*sin(j)*100.0f);
      return res;
  }


} // END class Artifact











//
