class Fingerprint {

    // properties
    PVector center_point;
    ArrayList <Vertex> spiral_vertices;
    float radius_1, radius_2;
    float radius_decrease_amount;

    Fingerprint(PVector center){
        center_point = center.copy();

        radius_1 = 190;
        radius_2 = 305;
        radius_decrease_amount = 0.15;

        create_fingerprint();
    }

    // main function used to shape form
    // in a simplified world, a loop-shaped fingerpint is a spiral with some noise
    void create_fingerprint(){

        spiral_vertices = new ArrayList<Vertex>();

        for (float a = 0; a < TWO_PI*11; a += 0.05){
            
            // set the position
            float x1 = radius_1 * sin(a);
            float y1 = radius_2 * cos(a);
            float z1 = noise(a) * 50;

            Vertex vertex_1 = new Vertex(x1, y1, z1);
            vertex_1.col = color(255);
            vertex_1.size = 2;

            spiral_vertices.add(vertex_1);

            float random_amount = noise(x1, y1) * 0.1;

            println("random amount: " + random_amount);

            // decrease the radius in order to create the spiral
            // and add some variance
            radius_1 -= radius_decrease_amount;
            radius_2 -= radius_decrease_amount + random(-1.1, 1.1);
        }
    }

    // shake the vertices a bit
    void update(){

        float amplitude = 0.09;
        float period = 120;

        for (int i = 0; i < spiral_vertices.size(); i++){
            Vertex vertex = spiral_vertices.get(i);

            period += random(-0.001, 0.001);

            // do some oscillation
            float displacement_x = amplitude * cos((TWO_PI * frameCount / (period * 0.3)) + i);
            float displacement_z = amplitude * cos((TWO_PI * frameCount / period) + i);
            
            vertex.position.x += displacement_x + random(-0.05, 0.05);
            vertex.position.z += displacement_z;
        }
    }
}