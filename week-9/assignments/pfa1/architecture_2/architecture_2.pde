/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    @title :  Week 9 Assignment, Programming for Artists 1
    @author:  vvz3n
    @details: Inspired by the Auroville city architecture, https://butdoesitfloat.com/Auroville-belongs-to-nobody-in-particular
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

import peasy.*;

PeasyCam cam;
boolean drawAxis = false;
boolean drawGrid = false;

ArrayList <PVector> positions;
ArrayList <PVector> sizes;
ArrayList <PVector> rotations;
ArrayList <Integer> buildingTypes;
ArrayList <Integer> colors;

// CONSTANTS
int CELL_SIZE = 30;
int NUM_CELLS = 40;
int SIZE = CELL_SIZE * NUM_CELLS;
int BOXES_NUM = NUM_CELLS * NUM_CELLS;

boolean IS_ORTHO = true;
boolean debug = false; // press d to enter debug mode

// CAMERA MOVEMENT
float rotationAngle = 0.0;
float rotationSpeed = 0.001;

void setup(){
    size(1280, 720, P3D);

    if (IS_ORTHO){
        ortho();
    }
    else {
        cam = new PeasyCam(this, 1000); // sketch reference, current distance away from 0,0,0
        cam.setMinimumDistance(200);
        cam.setMaximumDistance(4000);
    }

    // initialises data structures
    positions = new ArrayList<PVector>();
    sizes = new ArrayList<PVector>();
    rotations = new ArrayList<PVector>();
    buildingTypes = new ArrayList<Integer>();
    colors = new ArrayList<Integer>();

    generateBuildings();
}


void draw(){
    
    background(30);
    //background(255);

    if (IS_ORTHO){
        translate(width / 2, height / 2, 0);
        //rotateY(3.0);
        //rotateX(map(mouseX, 0, width, -TWO_PI, TWO_PI));
        rotateX(map(748, 0, width, -TWO_PI, TWO_PI));
        // rotate the view
        rotationAngle += rotationSpeed;
        rotateZ(rotationAngle);
    }

    if(drawAxis || debug) drawAxis();
    if(drawGrid || debug) drawGrid(NUM_CELLS, CELL_SIZE);

    sphereDetail(16);

    // lighting
    lights();
    directionalLight(80, 80, 80, map(560, 0, width, -1, 1), map(248, 0, height, -1, 1), 0);

    // reference circles
    if (debug){
        pushStyle();
        pushMatrix();
            stroke(255);
            strokeWeight(3);
            noFill();
            drawCircle(SIZE/2, 0, 32);
            drawCircle(SIZE/4, 0, 32);
            drawCircle(SIZE/8, 0, 32);
            fill(255, 0, 0);
            drawCircle(SIZE/16, 0, 32);
        popMatrix();
        popStyle();
    }

    // draw the buildings
    for (int i = 0; i < positions.size(); i++){

        fill(colors.get(i));

        // pick the kind of building to draw
        switch(buildingTypes.get(i)){
            // box
            case 1:
                drawBuilding1(positions.get(i), sizes.get(i), rotations.get(i));
                break;
            // cylinder
            case 2:
                drawBuilding2(positions.get(i), sizes.get(i), rotations.get(i));
                break;
        }
    }

    drawCenterSphere();
}

/*-------------------------------------------------
@brief:   Generates the pos, rot and sizes of all the buildings
@args:    
@details: 
@return:  
-------------------------------------------------*/
void generateBuildings(){

    for (float angle = 0; angle < TWO_PI; angle+=0.019){

        int dice = floor(random(0, 6));

        // FIRST OUTER ROW
        float outerRadius = SIZE/2 + random(-SIZE/4, -30);
        //outerRadius += map(noise(angle * 400), 0, 1, -SIZE/4, 0);
        
        PVector sz = new PVector(random(10, 70), random(20, 50), random(10, 40));  // w, h, d
        PVector pos = new PVector(outerRadius * cos(angle), outerRadius * sin(angle), sz.z / 2); // x, y, z
        PVector rot = new PVector(0, 0, angle); // rx, ry, rz
        int col = floor(random(0, 220));
        col = floor(map(noise(angle * 2), 0, 1, 20, 245)) + floor(random(-65, 65));

        int buildingType = 1;
        // only the shorter buildings show be circular
        if (sz.z < 15 && dice <= 2){
            buildingType = 2;
        }

        // Fill array lists
        positions.add(pos);
        sizes.add(sz);
        rotations.add(rot);
        buildingTypes.add(buildingType);
        colors.add(col);
        
        // SECOND OUTER ROW
        float secondOuterRadius = SIZE/4 + random(-SIZE/8, 0);
        sz = new PVector(random(10, 60), random(20, 40), random(3, 20));  // w, h, d
        pos = new PVector(secondOuterRadius * cos(angle), secondOuterRadius * sin(angle), sz.z / 2); // x, y, z
        rot = new PVector(0, 0, angle); // rx, ry, rz
        col = floor(map(noise(angle * 4), 0, 1, 20, 245)) + floor(random(-65, 65));

        dice = floor(random(0, 6));
        if (dice >= 2){
            buildingType = 1;
        }
        else {
            buildingType = 2;
        }

        // Fill array lists
        positions.add(pos);
        sizes.add(sz);
        rotations.add(rot);
        buildingTypes.add(buildingType);
        colors.add(col);

        // THIRD OUTER ROW
        float thirdOuterRadius = SIZE/8 + random(-SIZE/16, 0);
        sz = new PVector(random(5, 20), random(5, 10), random(2, 8));  // w, h, d
        pos = new PVector(thirdOuterRadius * cos(angle), thirdOuterRadius * sin(angle), sz.z / 2); // x, y, z
        rot = new PVector(0, 0, angle); // rx, ry, rz
        col = floor(map(noise(angle * 8), 0, 1, 20, 245)) + floor(random(-65, 65));

        buildingType = 1;

        // Fill array lists
        positions.add(pos);
        sizes.add(sz);
        rotations.add(rot);
        buildingTypes.add(buildingType);
        colors.add(col);

        // MOST INNER ROW
        if (floor(random(1,5)) == 2){

            float innerRadius = SIZE/16 + random(-SIZE/32, -30);
            sz = new PVector(SIZE/32, random(8, 16), random(1, 4));  // w, h, d
            pos = new PVector(innerRadius * cos(angle), innerRadius * sin(angle), sz.z / 2); // x, y, z
            rot = new PVector(0, 0, angle); // rx, ry, rz
            col = floor(map(noise(angle * 16), 0, 1, 20, 245)) + floor(random(-65, 65));

            buildingType = 1;

            // Fill array lists
            positions.add(pos);
            sizes.add(sz);
            rotations.add(rot);
            buildingTypes.add(buildingType);
            colors.add(col);
        }
    }
}

/*-------------------------------------------------
@brief:   Draw the center sphere
@args:    
@details: 
@return:  
-------------------------------------------------*/
void drawCenterSphere(){
    
    pushStyle();
    pushMatrix();
        noStroke();
        fill(255);
        sphere(30);
    popMatrix();
    popStyle();
}

/*-------------------------------------------------
@brief:   Draws the grid
@args:    
@details: 
@return:  
-------------------------------------------------*/
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

/*-------------------------------------------------
@brief:   Draw the origin reference axis
@args:    
@details: 
@return:  
-------------------------------------------------*/
void drawAxis(){
    
    pushStyle();

    int len = 300;
    
    strokeWeight(1);
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