//////////////////////////////////
// BARE BOIDS
// liorbengai
// 2018
//
// Based on pseudocode from Conrad Parker
// http://www.kfish.org/boids/pseudocode.html
//
// For more info:
//https://en.wikipedia.org/wiki/Boids
//http://www.cs.toronto.edu/~dt/siggraph97-course/cwr87/
//https://www.youtube.com/watch?v=86iQiV3-3IA
//////////////////////////////////

ArrayList<Boid> boids;

void setup(){
  size(800,400);
  boids = new ArrayList(); // init container
}

void draw(){
  background(32);
  int s = boids.size();
  for(int i = 0 ; i < s;i++){
    boids.get(i).update();
  }
}

void mousePressed(){
  Boid tempB = new Boid(mouseX, mouseY );
  boids.add(tempB);
}
