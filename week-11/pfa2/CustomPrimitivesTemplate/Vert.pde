//////////////////////////////////
// Vertex class
// liorbengai
// Jan 2018
///////////////////////////////

class Vert{

  // only one property
  PVector position;

  // Constructor
  // This gets called when using the 'new' keyword
  Vert(float x, float y, float z){
    // set position according to parameters
    position = new PVector(x, y, z);
  }

  void update(){
    // modulate the position in real time
    float n = mouseX  * 0.001;

    // use with the sphere...
    // position.x += random(-n,n);
    // position.y += random(-n,n);
    // position.z += random(-n,n);

    // use with the plane...
    // position.z = noise(( (position.x + - 1000) + frameCount) * n, (position.y - 1000) * n) * mouseY;
  }

} // class Vert
