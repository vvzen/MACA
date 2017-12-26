import peasy.*;

PeasyCam cam;
boolean drawAxis = true;
boolean drawGrid = true;

ArrayList <PVector> positions;
ArrayList <PVector> sizes;
ArrayList <PVector> rotations;
ArrayList <PVector> boxesColors;

int BOXES_NUM = 1000;

void setup(){
    size(1280, 720, P3D); // Use the p3d renderer

    cam = new PeasyCam(this, 2000); // sketch reference, current distance away from 0,0,0
    cam.setMinimumDistance(0);
    cam.setMaximumDistance(5000);

    // initialises data structures
    positions = new ArrayList<PVector>();
    sizes = new ArrayList<PVector>();
    rotations = new ArrayList<PVector>();

    // setup the building
    for(int i = 0; i < BOXES_NUM; i++){

        addBox();
    }
}

void draw(){

    background(127);
    
    if(drawAxis) drawAxis();
    if(drawGrid) drawGrid(30, 100);

    // draw all of the boxes
    for (int i = 0; i < positions.size(); i++){
       
       pushMatrix();
       
    //    fill(colors.get(i).x, colors.get(i).y, colors.get(i).z);
       translate(positions.get(i).x, positions.get(i).y, positions.get(i).z);
       rotateX(rotations.get(i).x);
       rotateY(rotations.get(i).y);
       rotateZ(rotations.get(i).z);
       box(sizes.get(i).x, sizes.get(i).y, sizes.get(i).z); 
       
       popMatrix();
    }
    
    // box(random(10, 100), 200, 500);

    // pushMatrix();
    // translate(30, 0, 15);
    // sphere(30);
    // popMatrix();
    
}

void addBox(){

    int maxDistance = 600; 

    // TODO: spawn the boxes in a consistent way so that they don't overlap
    // keep track of the position of every box

    PVector sz = new PVector(random(20, 100), random(20, 100), random(20, 100));  // w, h, d
    PVector pos = new PVector(random(-maxDistance, maxDistance), random(-maxDistance, maxDistance), sz.z/2); // x, y, z 
    // PVector rot = new PVector(random(-PI, PI), random(-PI, PI), random(-PI, PI)); // rx, ry, rz
    PVector rot = new PVector(0,0,0); // rx, ry, rz
    // change green values
    //PVector mycol = new PVector(random(200, 255), 255, random(200, 255));
    PVector mycol = new PVector(255, 255, 255);

    boolean matching = false;

    float greatestDimension = (sz.x > sz.z) ? sz.x : sz.z;

    int i = 0;
    while (!matching && i < positions.size()){

        // if the current position is different from all the existing positions, then add it
        // else, find a new one
        PVector currentPos = positions.get(i);
        PVector currentSize = sizes.get(i);

        float currentGreatestDimension = (currentSize.x > currentSize.y) ? currentSize.x : currentSize.y;
        float minimumTolerableDistance = (currentGreatestDimension / 2) + (greatestDimension / 2);
        
        if (dist(pos.x, pos.y, pos.z, currentPos.x, currentPos.y, currentPos.z) < minimumTolerableDistance){
            pos.add(new PVector(sz.x * 2, sz.y * 2, 0));
            // pos = new PVector(random(-maxDistance, maxDistance), random(-maxDistance, maxDistance), sz.z/2);
        }

        i++;
    }
    
    positions.add(pos);
    sizes.add(sz);
    rotations.add(rot);
    // boxesColors.add(mycol);
}

// draw the origin reference axis
void drawAxis(){
    
    pushStyle();

    int len = 300;
    
    strokeWeight(2);
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

// draw the xy grid
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