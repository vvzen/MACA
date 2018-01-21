/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    @title : Study 1 - RANDOM. 3D point cloud primitive
    @date :  21/01/2018
    @author: vvz3n
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

import peasy.*;

PeasyCam cam;

DNASpiral dna;

void setup(){
    size(540, 960, P3D);

    // peasy cam stuff
    cam = new PeasyCam(this, 1000);
    cam.setMinimumDistance(50);
    cam.setMaximumDistance(5000);

    dna = new DNASpiral(new PVector(0, 0, 0));

    println("points size : " + dna.points.size());
}


void draw(){

    background(0);

    dna.update();

    pushStyle();

    stroke(255);
    strokeWeight(2);

    pushMatrix();
    translate(0, 0, -dna.height/2);
    
    beginShape(POINTS);
    // draw the points all at once
    // so that we're optimizing the work for the gpu
    // nice tip from Lior
    for (int i = 0; i < dna.points.size(); i++){
        PVector position = dna.points.get(i);
        vertex(position.x, position.y, position.z);
    }
    endShape();

    popMatrix();
    popStyle();

    drawAxis();
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
