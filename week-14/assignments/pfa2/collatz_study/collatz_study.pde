/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    @title : FUNCTIONAL. Collatz study
    @date :  27/01/2018
    @author: vvz3n
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

import peasy.*;
import controlP5.*;
import nervoussystem.obj.*; // for obj export

PeasyCam cam;
ControlP5 cp5;

// transformations
float angle_x;
float angle_y;
float translate_x;
float translate_y;
float y_rotation = 0.0;
float y_rotation_speed = 0.005;
float stroke_width;

// colors
// color bg_color = color(255, 255, 255);
color bg_color = color(5, 5, 5);
// color label_color = color(20, 20, 20);
color label_color = color(255, 255, 255);

// collatz
ArrayList<Integer> collatz_numbers;
ArrayList<Integer> input_numbers;

int branch_length = 8;
//float angle = 0;
int max_iterations = 30;

void setup(){

    size(1280, 720, P3D);
    ortho();

    setup_GUI();

    translate_x = width*0.5;
    translate_y = height-50;
    angle_x = 0;
    angle_y = 0;

    // cam = new PeasyCam(this, 1200);
    // cam.setMinimumDistance(20);
    // cam.setMaximumDistance(10000);

    input_numbers = new ArrayList<Integer>();

    // generate {max_iterations} of random numbers to be feed into the collatz function
    for (int i = 0; i < max_iterations; i++){
        
        int num = floor(random(0, max_iterations*10));

        // don't add two times the same number
        while (true){

            if (!input_numbers.contains(num)){
                input_numbers.add(num);
                break;
            }
            else {
                num = floor(random(0, max_iterations*10));
            }
        }
    }

    println("input numbers : " + input_numbers);
}

void draw(){
    
    background(bg_color);

    draw_collatz(this.g);

    draw_GUI();
}


void draw_collatz(PGraphics pg){
    
    pg.strokeWeight(stroke_width);

    y_rotation += y_rotation_speed;

    float rad_angle_x = radians(angle_x); 
    float rad_angle_y = radians(angle_y);

    pushMatrix();
    
    pg.translate(translate_x, translate_y, 0);
    pg.rotateY(y_rotation);

    //draw_axis();
    pg.pushStyle();
    for (int i = 0; i < input_numbers.size(); i++){
        pg.pushMatrix();
            collatz(pg, input_numbers.get(i), branch_length, rad_angle_x, rad_angle_y);
        pg.popMatrix();
    }
    pg.popStyle();

    popMatrix();
}

void export(String name){
    
    MeshExport mesh_output = (MeshExport) createGraphics(10, 10, "nervoussystem.obj.OBJExport", name + ".obj");
    
    beginRecord("nervoussystem.obj.OBJExport", name);
    
    mesh_output.beginDraw();
    
    this.draw_collatz(mesh_output);

    mesh_output.endDraw();
    mesh_output.dispose();
    
    endRecord();

    println("export finished");
}

// Using while approach instead of recursion
ArrayList<Integer> collatz(PGraphics pg, int n, float branchLength, float radAngleX, float radAngleY){

    ArrayList <Integer> collatz_numbers = new ArrayList<Integer>();

    // pg.beginShape(POINTS);
    pg.beginShape(LINE_STRIP);

    while(true){

        collatz_numbers.add(n);

        // set the colors
        float blue = 255 - collatz_numbers.size();
        float red = map(collatz_numbers.size(), 0, 100, 0, 255);
        
        pg.stroke(red, 0, blue);
        // make the first line
        pg.line(0, 0, 0, 0, -branchLength, 0);
        // move at the end of it
        pg.translate(0, -branchLength, 0);

        // if we reached one we're done
        if (n == 1){
            pg.endShape();
            return collatz_numbers;
        }
        // turn left or right depending on number parity
        else if (n % 2 == 0){
            pg.rotateX(radAngleX);
            pg.rotateY(radAngleY);
            n = n / 2;
        }
        else {
            pg.rotateX(-radAngleX);
            pg.rotateY(-radAngleY);
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

////////////////// GUI //////////////////
void setup_GUI(){
    cp5 = new ControlP5(this);
    cp5.setAutoDraw(false);

    cp5.addSlider("angle_x")
        .setPosition(20, 20)
        .setRange(-34, 34)
        .setColorCaptionLabel(label_color);
    
    cp5.addSlider("angle_y")
        .setPosition(20, 40)
        .setRange(-34, 34)
        .setColorCaptionLabel(label_color);

    cp5.addSlider("branch_length")
        .setPosition(20, 60)
        .setRange(1, 16)
        .setColorCaptionLabel(label_color);
    
    cp5.addSlider("stroke_width")
        .setPosition(20, 80)
        .setRange(0.5, 5)
        .setColorCaptionLabel(label_color);
    
    cp5.addSlider("translate_x")
        .setPosition(20, 100)
        .setRange(0, width)
        .setColorCaptionLabel(label_color);
    
    cp5.addSlider("translate_y")
        .setPosition(20, 120)
        .setRange(0, height)
        .setColorCaptionLabel(label_color);
}

void draw_GUI() {
  // do not move the camera while manipulating the gui
  if (cp5.isMouseOver()) {
    //cam.setActive(false);
  }
  else {
    //cam.setActive(true);
  }
  // draw the GUI outside of the camera's view
  hint(DISABLE_DEPTH_TEST);
  //cam.beginHUD();
  cp5.draw();
  //cam.endHUD();
  hint(ENABLE_DEPTH_TEST);
}

////////////////// EVENTS //////////////////
void mousePressed(){
    println("mouse : " + map(mouseX, 0, width, -90, 90));
}

void keyPressed(){

    switch (key){
        case 's':{
            saveFrame("vv_collatz.png");
            break;
        }
        case 'e':{
            export("collatz");
        }
    }
}