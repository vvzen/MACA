class DNASpiral {

    // properties
    PVector center_point;
    ArrayList <PVector> points;
    float radius;
    float z;
    float z_increment;
    float height;

    // methods
    DNASpiral(PVector center){
        center_point = center.copy();

        radius = 200;
        z = 0;
        z_increment = 75;

        create_dna();
    }

    // main function used to shape form
    void create_dna(){

        points = new ArrayList<PVector>();

        // create first spiral
        for (float a = 0; a < TWO_PI*4; a += 0.25){
            
            float x = radius * cos(a);
            float y = radius * sin(a);
            this.z += this.z_increment;
            PVector pos = new PVector(x, y, this.z);

            // add a point for the first spiral
            points.add(pos);

            x = radius * cos(a + PI);
            y = radius * sin(a + PI);
            PVector pos_2 = new PVector(x, y, this.z);

            // add a point for the second spiral
            points.add(pos_2);
        }

        this.height = this.z;

    }

    void update(){
        
        // TODO:
    }
}