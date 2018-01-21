/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    @title : Study 1 - RANDOM. 3D point cloud primitive
    @date :  21/01/2018
    @author: vvz3n
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

import peasy.*;

// PeasyCam cam;

DNASpiral dna;

float x_rotation = 0;
float rotation_speed = 0.02;

void setup(){
    size(500, 800, P3D);

    // peasy cam stuff
    // cam = new PeasyCam(this, 3000);
    // cam.setMinimumDistance(50);
    // cam.setMaximumDistance(7000);

    dna = new DNASpiral(new PVector(0, 0, 0));

    println("num of vertices : " + (dna.inner_vertices.size() + dna.spiral_vertices.size()));
}


void draw(){

    background(20);

    dna.update();

    pushStyle();

    pushMatrix();

    translate(width/2, height/2, 0);
    // translate(0, 0, 20);
    rotateX(23);
    // translate(0, 0, (-dna.height/2) - 300);
    translate(0, 2000, 0);

    rotateZ(x_rotation);
    
    // draw the vertices all at once
    // so that we're optimizing the work for the gpu
    // nice tip from Lior

    beginShape(POINTS);
    // two spirals
    for (int i = 0; i < dna.spiral_vertices.size(); i++){
        Vertex vertex = dna.spiral_vertices.get(i);
        stroke(vertex.col);
        strokeWeight(vertex.size);
        vertex(vertex.position.x, vertex.position.y, vertex.position.z);
    }
    endShape();

    beginShape(POINTS);
    // center vertices
    for (int i = 0; i < dna.inner_vertices.size(); i++){
        Vertex vertex = dna.inner_vertices.get(i);
        stroke(vertex.col);
        strokeWeight(vertex.size);
        vertex(vertex.position.x, vertex.position.y, vertex.position.z);
    }
    endShape();

    // drawAxis();
    
    popStyle();
    popMatrix();

    x_rotation += rotation_speed;
}

void mousePressed(){
    println("mouse X: " + mouseX);
}

// draw xyz reference axis
void drawAxis(){

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
