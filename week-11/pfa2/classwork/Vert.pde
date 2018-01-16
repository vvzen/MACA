class Vert {

    // properties
    PVector position;
    float radius;
    color col;

    // constructor
    Vert(float x, float y, float z){
    
        position = new PVector(x, y, z);
        radius = 1;
        col = color(255, 255, 255);
    };
    
    // methods

    void update(){
        // change position
        // position.z = random(-100, 100);
        // float scaleFactor = mouseX * 0.0001;
        float scaleFactor = 255 * random(0.0000050, 0.0000055) * 1;
        float animationOffset = (frameCount * 0.005);

        position.z = noise(position.x * scaleFactor + animationOffset, position.y * scaleFactor) * 512;

        col = color(map(position.z, 0, 512, 0, 255), map(position.z, 0, 200, 0, 255), map(position.z, 0, 200, 0, 255));
        
        // position.z += random(-0.7, 0.7);
        
        // float d = dist(0, 0, 0, position.x, position.y, position.z);
        // radius = map(d, 0, mouseY, 3, 0.5);
        // radius = map(position.z, 0, 512, 3, 0.2);
    }

}