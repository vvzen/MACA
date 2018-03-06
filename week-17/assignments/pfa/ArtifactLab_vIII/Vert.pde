//////////////////////////////////
// Vertex class
// A simple data object wrapper for a 3D vector
// liorbengai
// Jan 2018

// 1. PROPERTIES
// 2. CLASS SETUP
// 3. UPDATE
///////////////////////////////

class Vert{

  ////////////////////////
  // CLASS PROPERTIES
  //////////////////////

  PVector initPosition;
  PVector position;
  color col;


  ////////////////////////
  // CLASS SETUP
  //////////////////////

  // Constructor
  Vert(float x, float y, float z){
    // set position according to parameters
    this.initPosition  = new PVector(x, y, z);
    this.position = initPosition.copy();
  }
  
  Vert(float x, float y, float z, color col){
    // set position according to parameters
    this.initPosition  = new PVector(x, y, z);
    this.position = initPosition.copy();
    this.col = col;
  }

  ////////////////////////
  // UPDATE PROPERTIES
  //////////////////////

  // modulate the position on runtime
  void update(){

    // modulate the current position by adding to initPos
    position = PVector.add(initPosition, getSinMod() );
  }

  // move according to the following forumla
  PVector getSinMod(){
    PVector res = new PVector(0,0,0);
    float freq = param_A *0.0001;
    float amp = param_B * 0.5;
    res.z  =  ( sin( (freq) * position.y ) + cos( position.x * (freq+PI)) ) * amp;
    return res;
  }

} // class Vert












//
