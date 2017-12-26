import peasy.*;

PeasyCam cam;
boolean drawAxis = true;
boolean drawGrid = true;

void setup(){
    size(1280, 720, P3D); // Use the p3d renderer

    cam = new PeasyCam(this, 2000); // sketch reference, current distance away from 0,0,0
    cam.setMinimumDistance(0);
    cam.setMaximumDistance(5000);

    
}

void draw(){

    background(127);
    
    if(drawAxis) drawAxis();
    if(drawGrid) drawGrid(30, 100);


    
    // box(random(10, 100), 200, 500);

    // pushMatrix();
    // translate(30, 0, 15);
    // sphere(30);
    // popMatrix();
    
}

void drawAxis(){
    
    pushStyle();

    int len = 300;
    
    strokeWeight(4);
    // X
    stroke(255, 0, 0);
    line(0, 0, 0, len, 0, 0);
    // Y
    stroke(0, 255, 0);
    line(0, 0, 0, 0, len, 0);
    // Z
    stroke(0, 0, 255);
    line(0, 0, 0, 0, 0, len);
    
    strokeWeight(10);
    // X
    stroke(255, 0, 0);
    point(len, 0, 0);
    // Y
    stroke(0, 255, 0);
    point(0, len, 0);
    // Z
    stroke(0, 0, 255);
    point(0, 0, len);

    popStyle();
}

void drawGrid(int numCells, int cellSize){

    int size = numCells * cellSize;
    pushMatrix();
    translate(- (size / 2), - (size / 2));

    for (int i = 0; i <= numCells; i++){
        // rows
        line(i*cellSize, 0, 0, i*cellSize, size, 0);
        // cols
        line(0, i*cellSize, 0, size, i*cellSize, 0);
    }
    popMatrix();
}

void keyPressed(){
    if (key == 'a'){
        drawAxis = !drawAxis;
    }
    if (key == 'g'){
        drawGrid = !drawGrid;
    }
}