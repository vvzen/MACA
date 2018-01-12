class Thing {

    PVector center;
    float radius;
    int num_points;
    PVector offset;
    int curve_type;

    // constructor
    Thing(PVector _center, float _radius){

        center = _center;
        radius = _radius;
        num_points = floor(random(4, 16));
        offset = new PVector(random(0, 22), random(0, 42), random(0, 32));

        // init curve type
        curve_type = floor(random(0, 2));
    }

    void update(){
        float noise_multiplier = 0.001;
        float noise_input = millis() * noise_multiplier * (center.x * noise_multiplier); 
        float noise_x = map(noise(noise_input), 0, 1, -0.5, 0.5);
        float noise_y = map(noise(noise_input + 500), 0, 1, -0.5, 0.5);
        float noise_z = map(noise(noise_input + 200), 0, 1, -0.5, 0.5);
        PVector noise_amount = new PVector(noise_x, noise_y, noise_z);
        offset.add(noise_amount);
    }

    void draw(){

        pushMatrix();
        translate(center.x, center.y, center.z);
        // noStroke();
        
        // beginShape();

        float increment = TWO_PI / num_points;

        for (float a = 0, i = 0; a <= TWO_PI; a+=increment, i++){
            rotate(a);
            float x, y, z;
            if (i % 2 == 0){
                x = sin(a) * (radius + offset.x);
                y = cos(a) * (radius + offset.y);
                z = cos(a) * (radius + offset.y);
            }
            else {
                x = sin(a) * ((radius / 2) + offset.x);
                y = cos(a) * ((radius / 2) + offset.y);
                z = cos(a) * ((radius / 2) + offset.y);
            }

            stroke(255);
            line(0, 0, 0, x, y, z);
            noStroke();

            pushMatrix();
            translate(x, y, z);

            if (curve_type == 0){
                box(radius);
            }
            else {
                // ellipse(x, y, radius, radius);
                sphere(radius);
            }
            popMatrix();
            
        }

        // endShape(CLOSE);

        popMatrix();
    }
}