/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    @title : Study 1 - RANDOM. 3D point cloud primitive
    @date :  21/01/2018
    @author: vvz3n
    @brief : A study of fingerprints using spirals and randomness.
            Probably much more interesting results could be obtained using 
            a reaction diffusion approach or a vector field with a relatively
            small flock simulation.
            This code can be found online here: https://github.com/VVZen/MACA/tree/master/week-11/assignments/pfa2/point_cloud_2
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

import peasy.*;
import nervoussystem.obj.*; // for obj export

// PeasyCam cam;

Fingerprint fingerprint;

// dna
DNASpiral dna;
float dna_rotation_x = 0.47916603;
float dna_rotation = 0;
float rotation_speed = 0.025;

// fingerprint
float fingerprint_rotation_x = 2.369164;
float fingerprint_rotation_y = 2.969164;
float fingerprint_rotation_z = 0.17;

// camera
float offset_x = 0;
float offset_z = -435.41663;
float rotation_z = 0.80;

void setup(){
    size(960, 540, P3D);

    // peasy cam stuff
    // cam = new PeasyCam(this, 3000);
    // cam.setMinimumDistance(50);
    // cam.setMaximumDistance(7000);

    // setup the shapes
    fingerprint = new Fingerprint(new PVector(0, 0, 0));
    dna = new DNASpiral(new PVector(0, 0, 0));
}


void draw(){

    background(20);

    dna.update();
    fingerprint.update();

    pushMatrix();
    
    // get the places at the right places
    translate(100, 0, 0);
    translate(width/2, height/2, 0);
    
    // offset_z = map(mouseX, 0, width, -1000, 1000);
    translate(offset_x, 0, offset_z);
    
    // rotation_z = map(mouseX, 0, width, -40, 40);
    rotateX(rotation_z);

    // draw the fingerprint
    fingerprint_rotation_x += rotation_speed * 0.3;
    pushMatrix();
        translate(100, 190, 190);
        rotateX(fingerprint_rotation_x);
        rotateY(-fingerprint_rotation_y);
        rotateZ(fingerprint_rotation_z);
        // draw_axis();
        fingerprint.draw(this.g);
    popMatrix();

    translate(-330, 390, 0);
    
    // draw the dna
    pushMatrix();
        // dna_rotation_x = map(mouseX, 0, width, -10, 10);
        rotateX(dna_rotation_x);
        rotateY(0.12);
        rotateZ(dna_rotation);
        dna.draw(this.g);
    popMatrix();
    
    popMatrix();

    dna_rotation += rotation_speed;
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

// EVENTS
void mousePressed(){
    println("mouse X: " + mouseX);
    println("offset_z: " + offset_z);
    println("rotation_z: " + rotation_z);
    println("dna_rotation_x: " + dna_rotation_x);
    println("fingerprint_rotation_x: " + fingerprint_rotation_x);

}

void keyPressed(){

    switch (key){
        case 's':{
            saveFrame("vv_pcloud_random.png");
            break;
        }
        case 'e':{
            dna.export("dna");
            fingerprint.export("fingerprint");
        }
    }
}
