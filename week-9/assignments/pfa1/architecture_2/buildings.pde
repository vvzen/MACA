/*-------------------------------------------------
@brief:   Draw building of type 1 (box)
@args:    pos, size and rotation as 3d PVector
@details: 
@return:  
-------------------------------------------------*/
void drawBuilding1(PVector pos, PVector size, PVector rotation){
    
    pushStyle();
    noStroke();
    //stroke(0);
    //strokeWeight(1);

    pushMatrix();
        translate(pos.x, pos.y, pos.z);
        rotateZ(rotation.z);
        box(size.x, size.y, size.z);
        //sphere(40);

    popMatrix();

    popStyle();

}

/*-------------------------------------------------
@brief:   Draw building of type 2 (cylinder)
@args:    pos, size and rotation as 3d PVector
@details: 
@return:  
-------------------------------------------------*/
void drawBuilding2(PVector pos, PVector size, PVector rotation){
    
    pushStyle();
    noStroke();
    //stroke(0);
    //strokeWeight(1);

    pushMatrix();
        translate(pos.x, pos.y, pos.z);
        rotateZ(rotation.z);
        cylinder(size.x/2, size.z, 16);
        //box(size.x, size.y, size.z);
        //sphere(40);

    popMatrix();

    popStyle();

}