/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    @title : FUNCTIONAL. Initial study
    @date :  27/01/2018
    @author: vvz3n
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

import peasy.*;

PeasyCam cam;

int n = 117;
ArrayList<Integer> collatz_numbers;
ArrayList<PVector> coordinates;


void setup(){
    size(1280, 720, P3D);

    cam = new PeasyCam(this, 200);
    cam.setMinimumDistance(20);
    cam.setMaximumDistance(7000);

    collatz_numbers = collatz(n);

    coordinates = new ArrayList<PVector>();
    float angle = 16;
    float angle_increment = angle;
    for (int i = 0; i < 100; i++){
        float radius = 10.0;
        PVector pos = new PVector(0, 0, 0);
        if (i == 0){
            pos.x = 0;
            pos.y = 0;
        }
        else {
            PVector previous_pos = coordinates.get(i-1);
            pos.x = radius * cos(angle);
            pos.x -= previous_pos.x;
            pos.y = radius * sin(angle);
            pos.y -= previous_pos.y;
            angle += angle_increment;
        }
        pos.z = 0;

        coordinates.add(pos);
    }

    println("collatz of " + n + ": " + collatz_numbers);
}


void draw(){

    background(20);

    pushStyle();

    pushMatrix();

    //translate(map(mouseX, 0, width, -width*2, width*2), 0, 0);

    // draw_fingerprint();

    beginShape(POINTS);
    for (int i = 1; i < coordinates.size(); i++){

        PVector pos = coordinates.get(i);
        PVector previous_pos = coordinates.get(i-1);
        
        // stroke(255);
        // strokeWeight(1.5);

        strokeWeight(1);
        stroke(255);
        // vertex(pos.x, pos.y, pos.z);
        line(previous_pos.x, previous_pos.y, previous_pos.z, pos.x, pos.y, pos.z);
    }
    endShape();

    popStyle();

    draw_axis();

    popMatrix();
}

ArrayList<Integer> collatz(int n){

    ArrayList <Integer> collatz_numbers = new ArrayList<Integer>();
    
    while (true){
        collatz_numbers.add(n);
        if (n == 1){
            return collatz_numbers;
        }
        else if (n % 2 == 0){
            n = n / 2;
        }
        else {
            n = n * 3 + 1;
        }
    }
}

// draw xyz reference axis
void draw_axis(){

    float size = 100;

    pushStyle();

    stroke(255, 0, 0);
    line(-size, 0, 0, size, 0, 0);

    stroke(0, 255, 0);
    line(0, -size, 0, 0, size, 0);

    stroke(0, 0, 255);
    line(0, 0, -size, 0, 0, size);

    popStyle();
}