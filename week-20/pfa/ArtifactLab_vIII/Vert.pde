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
  // PROPERTIES
  //////////////////////
  PVector position;
  PVector velocity;
  Artifact parent;

  ////////////////////////
  // SETUP
  //////////////////////

  // Constructor
  Vert(float x, float y, float z, Artifact _parent){
    // set position according to parameters
    position = new PVector(x, y, z);
    velocity = new PVector(-1, 1, 1.5);
    parent = _parent;
  }

  ////////////
  // UPDATE
  //////////

  // modulate the position on runtime
  void update(){
    
    // add each behaviour to velocity
    velocity.add(separation());
    velocity.add(cohesion());
    velocity.add(alignment());

    velocity.limit(1.5);
    position.add(velocity);
    
    //TODO:
    //parent.vertices.get(i)
  }

  // SEPARATION
  PVector separation(){

    PVector result = new PVector(0, 0, 0);

    for (int i = 0; i < parent.vertices.size(); i++){

      Vert other = parent.vertices.get(i);
      float dist = position.dist(other.position);

      if (dist > 0 && dist < 20){
        result.sub(PVector.sub(other.position, position));
      }
    }

    // scale it appropriately
    // result.mult(0.07);
    result.mult(0.01 + 0.01 * param_A);

    return result;
  }
  
  // COHESION
  PVector cohesion(){

    PVector result = new PVector(0, 0, 0);
    int num_neighbours = 0;

    for (int i = 0; i < parent.vertices.size(); i++){

      Vert other = parent.vertices.get(i);
      float dist = position.dist(other.position);

      if (dist > 0 && dist < 40){
        num_neighbours++;
        result.add(other.position);
      }
    }

    if (num_neighbours == 0) return new PVector(0, 0, 0);

    // take the average
    result.div(num_neighbours);

    // point into that direction
    result.sub(position);

    // scale it appropriately
    result.mult(0.01 + 0.01 * param_B);

    return result;
  }

  // ALIGNMENT
  PVector alignment(){

    PVector result = new PVector(0, 0, 0);
    int num_neighbours = 0;

    for (int i = 0; i < parent.vertices.size(); i++){

      Vert other = parent.vertices.get(i);
      float dist = position.dist(other.position);

      if (dist > 0 && dist < 30){
        num_neighbours++;
        result.add(other.velocity);
      }
    }

    if (num_neighbours == 0) return new PVector(0, 0, 0);

    // take the average
    result.div(num_neighbours);

    // scale it appropriately
    result.mult(0.3 + 0.3 * param_C);

    return result;
  }

} // class Vert












//
