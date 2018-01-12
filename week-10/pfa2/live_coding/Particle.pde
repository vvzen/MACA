/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
// Classes
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
class Particle {

    // properties
    PVector position;
    PVector velocity;
    color col;
    float radius;
    int counter;

    // constructor
    Particle(PVector initPos, color initCol, float initRad){
        // setup the Particle object
        position = initPos;
        col = initCol;
        radius = initRad;
        velocity = new PVector(random(-1, 1), random(-1, 1));
    }

    // methods
    void update(){
        position.add(velocity);
        torus_bounds();
        // jiggle();
    }

    void draw(){
        fill(col);
        ellipse(position.x, position.y, radius, radius);
    }

    void torus_bounds(){
        if (position.x < -radius){
            position.x = width;
        }
        else if (position.x > width + radius){
            position.x = 0;
        }
        if (position.y < -radius){
            position.y = height;
        }
        else if (position.y > height + radius){
            position.y = 0; 
        }
    }

    void wall_bounds(){

    }

    void jiggle(){
        PVector jigg = new PVector(random(-1, 1), random(-1, 1));
        position.add(jigg);
    }
}