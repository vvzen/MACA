class Vert {

    // properties
    PVector position;

    // constructor
    Vert(float x, float y, float z){
    
        position = new PVector(x, y, z);

    };
    
    // methods

    void update(){
        // change position
        // position.z = random(-100, 100);
        float scaleFactor = mouseX * 0.0001;
        position.z = noise(position.x * scaleFactor + (frameCount * 0.001), position.y * scaleFactor) * 255;
        position.z += random(-0.7, 0.7);
    }

}