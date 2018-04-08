class Boid{

  PVector position;
  PVector velocity;

  // called at setup
  Boid( float x, float y ){
    position = new PVector(x,y);
    velocity = new PVector(random(-1,1), random(-1,1));
  }

  // called every frame
  void update(){

    // add each behaviour to velocity
    velocity.add(separate());
    velocity.add(cohesion());
    velocity.add(align());

    velocity.limit(2.0);
    position.add(velocity);

    borders();

    draw();
  }

  // STEER TO AVOID CROWDING LOCAL FLOCKMATES
  PVector separate(){
    PVector RES = new PVector(0,0);
    // query the entire flock
    for(int i = 0 ; i < boids.size();i++){
      Boid other = boids.get(i);
      float dist = position.dist(other.position);

      if(dist < 20 && dist > 0){
        // it's close enough >> add a difference vector
        RES.sub(PVector.sub(other.position, position));
      }
    }

    RES.mult(0.07);
    return RES;
  }

  // STEER TO MOVE TOWARDS THE AVARAGE POSITION OF LOCAL FLOCKMATES
  PVector cohesion(){
    PVector RES = new PVector(0,0);
    int numNeighbours = 0;

    // query the entire flock
    for(int i = 0 ; i < boids.size();i++){
      Boid other = boids.get(i);
      float dist = position.dist(other.position);

      if(dist < 40 && dist > 0){
        // its close enough >> add its position to the avarage
        RES.add(other.position);
        numNeighbours++;

        // draw a red line to other
        stroke(255,64);
        strokeWeight(1);
        line(position.x, position.y, other.position.x, other.position.y);
      }
    }

    if(numNeighbours == 0) return new PVector(0,0);

    RES.div(numNeighbours);
    RES.sub(position);
    RES.mult(0.01);
    return RES;
  }

  // STEER TOWARD THE AVARAGE HEADING OF LOCAL FLOCKMATES
  PVector align(){
    PVector RES = new PVector(0,0);
    int numNeighbours = 0;

    // query the entire flock
    for(int i = 0 ; i < boids.size();i++){
      Boid other = boids.get(i);
      float dist = position.dist(other.position);
      if(dist < 30 && dist > 0){
        // it's close enough >> add its velocity to the avarage
        RES.add(other.velocity);
        numNeighbours++;
      }
    }
    if(numNeighbours == 0) return new PVector(0,0);

    RES.div(numNeighbours);
    RES.mult(0.3);
    return RES;
  }

  // Follow a Toroidal space
  void borders(){
    // toroidal space
    if(position.x >= width){
      position.x = 0;
    }if(position.x < 0 ){
      position.x = width;
    }
    if(position.y >= height){
      position.y = 0;
    }if(position.y < 0 ){
      position.y = height;
    }
  }

  void draw(){
   stroke(220);
   strokeWeight(5);
   point(position.x, position.y);
  }
}
