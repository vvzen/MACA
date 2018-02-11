/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    @title : FUNCTIONAL. Collatz study
    @date :  27/01/2018
    @author: vvz3n
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

import peasy.*;
import controlP5.*;

PeasyCam cam;
ControlP5 cp5;

// transformations
float angle_x;
float angle_y;
float translate_x;
float translate_y;
float y_rotation = 0.0;
float y_rotation_speed = 0.005;

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

    // println("collatz of " + n + ": " + collatz_numbers);
    println("input numbers : " + input_numbers);
}

void draw(){
    background(bg_color);
    //stroke(255);
    strokeWeight(1);

    y_rotation += y_rotation_speed;

    float rad_angle_x = radians(angle_x); 
    float rad_angle_y = radians(angle_y); 

    pushMatrix();
    
    translate(translate_x, translate_y, 0);
    // translate(map(mouseX, 0, width, -300, 300), 0, 0);
    rotateY(y_rotation);

    //draw_axis();
    pushStyle();
    for (int i = 0; i < input_numbers.size(); i++){
        pushMatrix();
            collatz(input_numbers.get(i), branch_length, rad_angle_x, rad_angle_y);
        popMatrix();
    }
    popStyle();

    popMatrix();

    draw_GUI();
}

ArrayList<Integer> collatz(int n, float branchLength, float radAngleX, float radAngleY){

    ArrayList <Integer> collatz_numbers = new ArrayList<Integer>();

    beginShape(POINTS);

    while(true){

        collatz_numbers.add(n);

        float red = 0, blue = 0, green = 0;
        //red = map(n, 0, max_iterations*10, 0, 255);
        //blue = map(n, 0, max_iterations*10, 0, 255);
        red = 255 - collatz_numbers.size();
        green = 255 - collatz_numbers.size();
        blue = 255 - collatz_numbers.size();
        float col = map(collatz_numbers.size(), 0, 100, 0, 255);
        //green = 255 - collatz_numbers.size();
        //blue = 255 - collatz_numbers.size();
        
        // stroke(red, green, blue);
        stroke(col, 0, blue);
        line(0, 0, 0, 0, -branchLength, 0);

        // strokeWeight(3);
        // stroke(255, 0, 0);
        // vertex(0, 0, 0);

        translate(0, -branchLength, 0);
        // vertex(0, 0, 0);

        if (n == 1){
            endShape();
            return collatz_numbers;
        }
        else if (n % 2 == 0){
            rotateX(radAngleX);
            rotateY(radAngleY);
            n = n / 2;
        }
        else {
            rotateX(-radAngleX);
            rotateY(-radAngleY);
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
    
    cp5.addSlider("translate_x")
        .setPosition(20, 80)
        .setRange(0, width)
        .setColorCaptionLabel(label_color);
    
    cp5.addSlider("translate_y")
        .setPosition(20, 100)
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