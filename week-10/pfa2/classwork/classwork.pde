/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    @title : Classwork for current week
    @date :  09/01/2018
    @author: vvz3n
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

import peasy.PeasyCam;

Thing thing;
ArrayList<Thing> thingies = new ArrayList<Thing>();
final static int THINGIES_NUM = 30;

// 3d 
PeasyCam cam;

void setup(){
    size(1024, 512, P3D);

    cam = new PeasyCam(this, 400);

    for (int i = 0; i < THINGIES_NUM; i++){
        
        // draw thingies on a grid
        // PVector pos = new PVector(i * x_step, i * y_step);

        PVector pos = new PVector(random(-512, 512), random(-512, 512), random(-250, 250));
        thingies.add(new Thing(pos, random(2, 16)));
    }
}


void draw(){

    background(30);
                
    pushMatrix();
    // translate(-width/2, -height/2, 0);

    for (int i = 0; i < thingies.size(); i++){
        Thing thing = thingies.get(i);
        thing.update();
        thing.draw();
    }

    popMatrix();
}