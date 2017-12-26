/*
@description: Simple GUI for Glitching images.
@details:
Current (limited) workflow is to edit the original image channels and then glitch it.
You cannot edit the channels anymore after you glitched the image.
To restore the image to the original one, click the Restore button.
To save a frame of the edited image, click the Save button.

Glitching is possible thanks to the awesome work by Kim Asendorf : https://github.com/kimasendorf/ASDFPixelSort
I just added the RGB channel editing, for now.

@author: VVZen
*/

// GUI
import controlP5.*;
ControlP5 cp5;
Slider abc;
float RED = 1.0;
float GREEN = 1.0;
float BLUE = 1.0;
int glitchMode = 1;
int brightnessThreshold = 60;

// Images
PImage originalImage;
PImage glitchedImage;
boolean glitched = false;

void setup() {
    size(1024, 720);
    noStroke();
    cp5 = new ControlP5(this);

    cp5.addSlider("RED")
        .setPosition(width/4, height/32)
        .setRange(0, 2);
     
    cp5.addSlider("GREEN")
        .setPosition(width/4, height/32 + 20)
        .setRange(0, 2);
     
    cp5.addSlider("BLUE")
        .setPosition(width/4, height/32 + 40)
        .setRange(0, 2);
     
    cp5.addSlider("glitchMode")
        .setPosition(width/2, height/32)
        .setRange(0, 2)
        .setNumberOfTickMarks(3);

    cp5.addSlider("brightnessThreshold")
        .setPosition(width/2, height/64)
        .setRange(0, 255);

    cp5.addButton("glitch")
        .setPosition(width - width/2, height/16);

    cp5.addButton("restore")
        .setPosition(width - width/4, height/16);

    cp5.addButton("selectImage")
        .setPosition(width - width/6, height/16);
    
    cp5.addButton("saveImage")
        .setPosition(width - width/6 + 80, height/16);
  
    // reposition the Label for controller 'slider'
    //cp5.getController("slider").getValueLabel().align(ControlP5.LEFT, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0);
    //cp5.getController("slider").getCaptionLabel().align(ControlP5.RIGHT, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0);
    
    // use Slider.FIX or Slider.FLEXIBLE to change the slider handle
    // by default it is Slider.FIX
  
    originalImage = loadImage("moonwalk.jpg");
    glitchedImage = originalImage.copy();
  
}

void draw() {

    background(40);

    fill(20);
    rect(0,0,width,100);

    if(!glitched) {
        editRGB();
    }
    pushMatrix();
    translate(0, 100);
    image(glitchedImage, width/8, width/8, glitchedImage.width, glitchedImage.height);
    popMatrix();
}

// select image button pressed
void selectImage(){
    println("select image button clicked");
    selectInput("Please select an image", "fileSelected");
}

// main function for editing the RGB channels of the image
void editRGB(){

    originalImage.loadPixels();
    glitchedImage.loadPixels();
    
    // modify image pixels
    for (int x = 0; x < glitchedImage.width; x++){
        for (int y = 0; y < glitchedImage.height; y++){
            
            color current_pixel = originalImage.get(x, y);
            
            float imc_r = red(current_pixel) * RED;
            float imc_g = green(current_pixel) * GREEN;
            float imc_b = blue(current_pixel) * BLUE;
            
            int pos = x + y * glitchedImage.width;
            glitchedImage.pixels[pos] = color(imc_r, imc_g, imc_b);
        }
    }

    glitchedImage.updatePixels();
}

// glitch button pressed
void glitch(){

    // set the global vars required by the glitch
    initValues();

    // loop through columns
    while(column < glitchedImage.width-1) {
        //println("Sorting Column " + column);
        glitchedImage.loadPixels(); 
        sortColumn();
        column++;
        glitchedImage.updatePixels();
    }
    
    // loop through rows
    while(row < glitchedImage.height-1) {
        //println("Sorting Row " + column);
        glitchedImage.loadPixels(); 
        sortRow();
        row++;
        glitchedImage.updatePixels();
    }

    glitched = true;
}

// restore the image back its original state
void restore(){
    glitchedImage = originalImage.copy();

    cp5.getController("RED").setValue(1.0);
    cp5.getController("GREEN").setValue(1.0);
    cp5.getController("BLUE").setValue(1.0);

    glitched = false;
}

void fileSelected(File selection) {
    if (selection == null) {
        println("Window was closed or the user hit cancel.");
    }
    else {
        String imgPath = selection.getAbsolutePath();
        println("User selected " + imgPath);
        
        // TODO: check if file path is path to an image
    }
}

void saveImage(){
    glitchedImage.save("glitched.png");
}