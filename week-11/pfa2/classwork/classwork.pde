/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    @title : Live Coding Session
    @date :  16/01/2018
    @author: vvz3n
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

import peasy.*;

PeasyCam cam;

ArrayList<Vert> vertices;

void setup(){
    size(1280, 800, P3D);

    // peasy cam stuff
    cam = new PeasyCam(this, 1000);
    cam.setMinimumDistance(50);
    cam.setMaximumDistance(5000);

    // instantiate array list
    vertices = new ArrayList<Vert>();

    // fill it up with vertices
    int w = 127;
    int h = 127;
    float gap = 10;

    for (int i = 0; i < w; i++){
        for (int j = 0; j < h; j++){
            
            // tell it where should go
            PVector position = new PVector();
            Vert v = new Vert(i * gap - (w * gap / 2), j * gap - (h * gap / 2), 0);

            // store in the arraylist
            vertices.add(v);
        }
    }
}


void draw(){

    pushStyle();

    background(0);
    strokeWeight(4);
    stroke(255);
    noFill();

    // update all vertices
    for (int i = 0; i < vertices.size(); i++){
        vertices.get(i).update();
    }

    // draw all vertices
    // draw them all together, so it's faster
    // because we're sending them to the gpu just in one big step
    beginShape(POINTS);
    for (int i = 0; i < vertices.size(); i++){
        PVector p = vertices.get(i).position;
        vertex(p.x, p.y, p.z);
    }
    endShape();

    popStyle();

    drawAxis();
}

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