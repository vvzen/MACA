class Vertex {

    // properties
    PVector position;
    float size;
    color col;

    // constructor
    Vertex(float x, float y, float z){

        position = new PVector(x, y, z);
        size = 1;
        col = color(255, 255, 255);
    };

}