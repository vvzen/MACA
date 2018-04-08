import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class Boids extends PApplet {

//////////////////////////////////
// BARE BOIDS
// liorbengai
// 2018

// Based on pseudocode from Conrad Parker
// http://www.kfish.org/boids/pseudocode.html

// For more info:
//https://en.wikipedia.org/wiki/Boids
//http://www.cs.toronto.edu/~dt/siggraph97-course/cwr87/
//https://www.youtube.com/watch?v=86iQiV3-3IA
//////////////////////////////////


ArrayList<Boid> boids;

public void setup(){
  
  boids = new ArrayList(); // init container
}

public void draw(){
  background(32);
  int s = boids.size();
  for(int i = 0 ; i < s;i++){
    boids.get(i).update();
  }
}

public void mousePressed(){
  Boid tempB = new Boid(mouseX, mouseY );
  boids.add(tempB);
}
class Boid{

  PVector position;
  PVector velocity;

  // called at setup
  Boid( float x, float y ){
    position = new PVector(x,y);
    velocity = new PVector(random(-1,1), random(-1,1));
  }

  // called every frame
  public void update(){
    // add each behaviour to velocity
    velocity.add(separate());
    velocity.add(cohesion());
    velocity.add(align());

    velocity.limit(4.0f);
    position.add(velocity);
    borders();
    draw();
  }

  // STEER TO AVOID CROWDING LOCAL FLOCKMATES
  public PVector separate(){
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

    RES.mult(0.07f);
    return RES;
  }

  // STEER TO MOVE TOWARDS THE AVARAGE POSITION OF LOCAL FLOCKMATES
  public PVector cohesion(){
    PVector RES = new PVector(0,0);
    int numMeighbours = 0;

    // query the entire flock
    for(int i = 0 ; i < boids.size();i++){
      Boid other = boids.get(i);
      float dist = position.dist(other.position);

      if(dist < 40 && dist > 0){
        // its close enough >> add its position to the avarage
        RES.add(other.position);
        numMeighbours++;

        // draw a red line to other
        stroke(255,64);
        strokeWeight(1);
        line(position.x, position.y, other.position.x, other.position.y);
      }
    }

    if(numMeighbours == 0) return new PVector(0,0);

    RES.div(numMeighbours);
    RES.sub(position);
    RES.mult(0.01f);
    return RES;
  }

  // STEER TOWARD THE AVARAGE HEADING OF LOCAL FLOCKMATES
  public PVector align(){
    PVector RES = new PVector(0,0);
    int numMeighbours = 0;

    // query the entire flock
    for(int i = 0 ; i < boids.size();i++){
      Boid other = boids.get(i);
      float dist = position.dist(other.position);
      if(dist < 30 && dist > 0){
        // it's close enough >> add its velocity to the avarage
        RES.add(other.velocity);
        numMeighbours++;
      }
    }
    if(numMeighbours == 0) return new PVector(0,0);

    RES.div(numMeighbours);
    RES.mult(0.3f);
    return RES;
  }

  // Toroidal space
  public void borders(){
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

  public void draw(){
   stroke(220);
   strokeWeight(5);
   point(position.x, position.y);
  }
}
  public void settings() {  size(800,400); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "Boids" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
