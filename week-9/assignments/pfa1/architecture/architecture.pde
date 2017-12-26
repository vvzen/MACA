/* +++++++++++++++++++++++++++++++++++++++++++++++
    @title : 3d Architecture assignment for week 9
    @date :  10/12/17
    @author: vvz3n
+++++++++++++++++++++++++++++++++++++++++++++++++*/

import peasy.*;

PeasyCam cam;
boolean drawAxis = false;
boolean drawGrid = true;

ArrayList <PVector> positions;
ArrayList <PVector> sizes;
ArrayList <PVector> rotations;
ArrayList <Integer> buildingTypes;

// CONSTANTS
color DOME_COLOR = color(124, 255, 210);
color DOME_COLOR_2 = color(125, 255, 187);
color WALLS_COLOR = color(244, 246, 216);
int CITY_SIZE = 600;

int CELL_SIZE = 20;
int NUM_CELLS = 20;
int SIZE = CELL_SIZE * NUM_CELLS;
int BOXES_NUM = NUM_CELLS * NUM_CELLS;

void setup(){
    size(1280, 720, P3D); // use the 3d renderer

    // ortho();

    cam = new PeasyCam(this, 2000); // sketch reference, current distance away from 0,0,0
    cam.setMinimumDistance(200);
    cam.setMaximumDistance(4000);

    // initialises data structures
    positions = new ArrayList<PVector>();
    sizes = new ArrayList<PVector>();
    rotations = new ArrayList<PVector>();
    buildingTypes = new ArrayList<Integer>();

    // generate all the buildings
    generateBuildings(BOXES_NUM);

    println("total buildings: " + BOXES_NUM);
}

void draw(){

    background(104, 201, 205);
    
    // translate(width/2, height/4, -1000);
    // rotateX(map(84, 0, width, -TWO_PI, TWO_PI));
    // rotateZ(map(324, 0, height, TWO_PI, -TWO_PI));

    if(drawAxis) drawAxis();
    if(drawGrid) drawGrid(NUM_CELLS, CELL_SIZE);
    
    sphereDetail(16);

    lights();
    // ambientLight(10, 10, 10);
    directionalLight(80, 80, 80, map(560, 0, width, -1, 1), map(248, 0, height, -1, 1), 0);

    // drawGround(CITY_SIZE*10);

    pushMatrix();
        translate(-SIZE/2, -SIZE/2);

        pushMatrix();
        translate(CELL_SIZE/2, CELL_SIZE/2);

        for(int i = 0; i < BOXES_NUM; i++){
            
            if (i % 2 == 0){

                println("i is " + i);

                drawBuilding1(positions.get(i), sizes.get(i), rotations.get(i));

                // draw different kinds of buildings
                // switch(buildingTypes.get(i)){
                //     case 1:
                //         drawBuilding1(positions.get(i), sizes.get(i), rotations.get(i));
                //         break;
                //     case 2:
                //         drawBuilding2(positions.get(i), sizes.get(i), rotations.get(i));
                //         break;
                //     case 3:
                //         drawBuilding3(positions.get(i), sizes.get(i), rotations.get(i));
                //         break;
                //     }
            }
        }
        
        popMatrix();

        // pushMatrix();
        //     translate(x * CELL_SIZE, y * CELL_SIZE, 0);
        //     box(20, 20, height);
        // popMatrix();

    popMatrix();
}

/*-------------------------------------------------
@brief:   Draws buildings of type 1 (more rectangular)
@args:    the 3d position and size
@details: 
@return:  
-------------------------------------------------*/
void drawBuilding1(PVector position, PVector size, PVector rotation){

    pushStyle();
    //noStroke();

    // use the largest dimension as the source for the radius
    float largestDimension = size.x > size.y ? size.x : size.y;
    float smallestDimension = size.x < size.y ? size.x : size.y;

    pushMatrix();
        //rotateZ(rotation.z);
        translate(position.x, position.y, position.z);
        fill(WALLS_COLOR);
        box(size.x, size.y, size.z);
    
        pushMatrix();
            fill(DOME_COLOR_2);
            // box(size.x, size.y, size.z);
            translate(0, 0, size.z / 2);
            sphere((smallestDimension / 2) - (smallestDimension / 8));
        popMatrix();

    popMatrix();

    popStyle();
}

/*-------------------------------------------------
@brief:   Draws buildings of type 2 (cylindric)
@args:    the 3d position and size
@details: 
@return:  
-------------------------------------------------*/
void drawBuilding2(PVector position, PVector size, PVector rotation){

    pushStyle();
    //noStroke();

    pushMatrix();
        
        //rotateZ(rotation.z);

        translate(position.x, position.y, position.z);
        fill(WALLS_COLOR);
        cylinder(size.x, size.z, 32);
    
        pushMatrix();
            fill(DOME_COLOR);
            translate(0, 0, size.z / 2);
            sphere(size.x -  (size.x / 8));
        popMatrix();

    popMatrix();

    popStyle();
}

/*-------------------------------------------------
@brief:   Draws buildings of type 3 (a small complex)
@args:    the 3d position and size
@details: 
@return:  
-------------------------------------------------*/
void drawBuilding3(PVector position, PVector size, PVector rotation){

    pushStyle();
    //noStroke();

    pushMatrix();

        //rotateZ(rotation.z);
        // main building
        translate(position.x, position.y, position.z);
        fill(WALLS_COLOR);
        cylinder(size.x, size.z, 32);
        // top
        pushMatrix();
            fill(DOME_COLOR);
            translate(0, 0, size.z * 2/5);
            sphere(size.x - (size.x / 16));
        popMatrix();

        // second building
        pushMatrix();
            fill(WALLS_COLOR);
            translate(-size.x, 0, -size.z / 4);
            cylinder(size.x/2, size.z / 2, 32);
            // top
            pushMatrix();
                fill(DOME_COLOR);
                translate(0, 0, size.z - size.z *  3/4);
                sphere(size.x/2 - (size.x / 2 / 16));
            popMatrix();
        popMatrix();

        pushMatrix();
        // third
            fill(WALLS_COLOR);
            translate(size.x, 0, -size.z / 4);
            cylinder(size.x / 2, size.z / 2, 32);
            // top
            pushMatrix();
                fill(DOME_COLOR);
                translate(0, 0, size.z - size.z *  3/4);
                sphere(size.x/2 - (size.x / 2 / 16));
            popMatrix();
        popMatrix();

    popMatrix();

    popStyle();
}

/*-------------------------------------------------
@brief:   Generic function to generate buildings
@args:    num -> the number of buildings to generate 
@details: fills up the array lists with the pos,rot,scales of each building
@return:  void
-------------------------------------------------*/
void generateBuildings(int num){

    // TODO: spawn the boxes in a consistent way so that they don't overlap
    // keep track of the position of every box

    for (int i = 0; i < BOXES_NUM; i++){

        PVector sz = new PVector(CELL_SIZE, CELL_SIZE, random(30, 200));  // w, h, d
        PVector pos = new PVector(x * CELL_SIZE, y * CELL_SIZE, sz.z / 2); // x, y, z 
        PVector rot = new PVector(0, 0, 0); // rx, ry, rz

        int buildingType = 1;
        float ratio = sz.x / sz.y;

        if (ratio > 0.80 && ratio < 1.20 && sz.x < 40){
            buildingType = 1;
        }
        else if (sz.x > 80 && sz.z > 60 && sz.z < 100){
            buildingType = 3;
        }
        else if (sz.z < 80){
            buildingType = 1;
        }
        else if (sz.z < 120){
            buildingType = 2;
        }

        positions.add(pos);
        sizes.add(sz);
        rotations.add(rot);
        buildingTypes.add(buildingType);

    }

    for (int x = 0; x < NUM_CELLS; x++){
        for (int y = 0; y < NUM_CELLS; y++){

            PVector sz = new PVector(CELL_SIZE, CELL_SIZE, random(30, 200));  // w, h, d
            PVector pos = new PVector(x * CELL_SIZE, y * CELL_SIZE, sz.z / 2); // x, y, z 
            PVector rot = new PVector(0, 0, 0); // rx, ry, rz

            int buildingType = 1;
            float ratio = sz.x / sz.y;

            if (ratio > 0.80 && ratio < 1.20 && sz.x < 40){
                buildingType = 1;
            }
            else if (sz.x > 80 && sz.z > 60 && sz.z < 100){
                buildingType = 3;
            }
            else if (sz.z < 80){
                buildingType = 1;
            }
            else if (sz.z < 120){
                buildingType = 2;
            }

            positions.add(pos);
            sizes.add(sz);
            rotations.add(rot);
            buildingTypes.add(buildingType);
        }
    }

    // for (int i = 0; i < num; i++){

    //     PVector sz = new PVector(random(10, 100), random(10, 100), random(30, 200));  // w, h, d
    //     PVector pos = new PVector(random(-CITY_SIZE, CITY_SIZE), random(-CITY_SIZE, CITY_SIZE), sz.z/2); // x, y, z 
    //     // PVector rot = new PVector(random(-PI, PI), random(-PI, PI), random(-PI, PI)); // rx, ry, rz
    //     PVector rot = new PVector(0, 0, random(-TWO_PI, TWO_PI)); // rx, ry, rz

    //     int buildingType = 0;
    //     int dice = floor(random(0, 6));
    //     float ratio = sz.x / sz.y;

    //     if (ratio > 0.80 && ratio < 1.20 && sz.x < 40){
    //         buildingType = 1;
    //     }
    //     else if (sz.x > 80 && sz.z > 60 && sz.z < 100){
    //         buildingType = 3;
    //     }
    //     else if (sz.z < 80){
    //         buildingType = 1;
    //     }
    //     else if (sz.z < 120){
    //         buildingType = 2;
    //     }

    //     // if (dice >= 3){
    //     //     buildingType = 1;
    //     // }
    //     // else {
    //     //     buildingType = 2;
    //     // }
        
    //     positions.add(pos);
    //     sizes.add(sz);
    //     rotations.add(rot);
    //     buildingTypes.add(buildingType);
    // }
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

/*-------------------------------------------------
@brief:   Draws the ground
@args:    
@details: 
@return:  
-------------------------------------------------*/
void drawGround(int size){

    pushStyle();
    //noStroke();

    pushMatrix();
        translate(0, 0, 0);
        fill(46, 92, 18);
        box(size, size, 2);
    popMatrix();

    popStyle();
}

/*-------------------------------------------------
@brief:   Draws a cylinder
@args:    
@details: taken from http://vormplus.be/blog/article/drawing-a-cylinder-with-processing
@author:  Jan Vantomme
@return:  
-------------------------------------------------*/
void cylinder(float r, float h, int sides){

    float angle = 360 / sides;
    float halfHeight = h / 2;

    // draw top shape
    beginShape();
    for (int i = 0; i < sides; i++) {
        float x = cos( radians( i * angle ) ) * r;
        float y = sin( radians( i * angle ) ) * r;
        vertex( x, y, -halfHeight );    
    }
    endShape(CLOSE);

    // draw bottom shape
    beginShape();
    for (int i = 0; i < sides; i++) {
        float x = cos( radians( i * angle ) ) * r;
        float y = sin( radians( i * angle ) ) * r;
        vertex( x, y, halfHeight );    
    }
    endShape(CLOSE);

    // draw body
    beginShape(TRIANGLE_STRIP);
    for (int i = 0; i <= sides + 1; i++) {
        float x = cos( radians( i * angle ) ) * r;
        float y = sin( radians( i * angle ) ) * r;
        vertex( x, y, halfHeight);
        vertex( x, y, -halfHeight);    
    }
    endShape(CLOSE);
}

////////////////////////////
////////  EVENTS  //////////
////////////////////////////
void keyPressed(){
    if (key == 'a'){
        drawAxis = !drawAxis;
    }
    if (key == 'g'){
        drawGrid = !drawGrid;
    }
    println(mouseX);
    println(mouseY);
}