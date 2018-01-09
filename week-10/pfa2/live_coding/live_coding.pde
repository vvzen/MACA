/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    @title : Live coding session in class, OOP
    @date :  09/01/2018
    @author: vvz3n
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

ArrayList<Particle> system;
int frame_counter;

void setup(){
    size(1024, 576);
    system = new ArrayList<Particle>();
    
    for (int i = 0; i < 1000; i++){
        PVector pos = new PVector(random(width), random(height));
        color col = color(random(255), random(255), random(255));
        float rad = random(5, 20);
        system.add(new Particle(pos, col, rad));
    }
}

void draw(){
    background(255);
    
    noStroke();
    for (int i = 0; i < system.size(); i++){
        Particle particle = system.get(i);
        particle.update();
        particle.draw();
    }
}