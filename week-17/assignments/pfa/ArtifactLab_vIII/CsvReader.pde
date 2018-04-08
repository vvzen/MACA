public class CsvReader extends Artifact{

    String[] lines;
    Table table;

    // scale - this controls the resolution of the final print
    float unit = 0.5;
    // counter vars
    int start = 1;
    int end = 19999;

    // Constructor
    CsvReader(){
        super();

        // get the data as an array of strings
        // lines = loadStrings("hs_alt_CHM1_1.1_chr1.mfa");
        table = loadTable("cuckoos_cleaned.csv", "header");
        println(table.getRowCount() + " total rows in table");

        vertices = new ArrayList<Vert>();

        // I skip some of the points since I'm on a macbook air
        // and the building of the geo inside houdini is taking too much time!
        int skip = 3;

        // loop through dataset
        for (int i = 0; i < table.getRowCount(); i+=skip){
        // for (TableRow row : table.rows()) {
    
            TableRow row = table.getRow(i);

            float lat = row.getFloat("location-lat");
            float lon = row.getFloat("location-long");
            // float alt = row.getFloat("argos:altitude");

            // id of the bird
            String id = row.getString("tag-local-identifier");
            String isOutlier = row.getString("algorithm-marked-outlier");
            //String name = row.getString("individual-taxon-canonical-name");

            // for each bird use a different color
            color col = color(255, 255, 255);


            // in order to export each bird path singularly
            // I'm just commenting each if branch for the other birds
            // if (id.equals("126694")){
            //     col = color(141, 31, 177);
                
            //     PVector pos = sphericalToCartesian(lat, lon, 1000);
            //     pushVert(pos, col);
            // }
            // if (id.equals("126695")){
            //     col = color(151, 25, 232);
                
            // }
            // if (id.equals("126696")){
            //     col = color(41, 86, 255);
            // }
            if (id.equals("126697")){
                col = color(25, 232, 229);
                PVector pos = sphericalToCartesian(lat, lon, 1000);
                pushVert(pos, col);
            }
            // if (id.equals("126698")){
            //     col = color(41, 255, 68);
            // }

            // if (isOutlier == "True"){
            //     println("outlier!");
            // }
        }

    }

    // overriding from super
    public void setup(){
        
    }

    public void update(){
        
        for(int i = 0; i < vertices.size();i++){
            float scaleFactor = param_A * 0.1;
            vertices.get(i).update();
            // vertices.get(i).position.mult(scaleFactor);
        }
    }

    // see https://en.wikipedia.org/wiki/Spherical_coordinate_system
    PVector sphericalToCartesian(float lat, float lon, float radius){
    
        float latitude = radians(lat);
        float longitude = radians(lon);

        float x = radius * cos(latitude) * cos(longitude);
        float y = radius * cos(latitude) * sin(longitude);
        float z = radius * sin(latitude);

        return new PVector(x, y, z);
    }

    // draws all vertices using LINE_STRIP to a provided PGraphics object
    public void draw(PGraphics pg){

        pushTransform(pg);
        
        // draw all lines
        pg.strokeWeight(map(param_A, 0, 255, 0.2, 5.0));
        pg.beginShape();
        for(int i = 0; i < vertices.size();i++){
            PVector p = vertices.get(i).position;
            pg.stroke(vertices.get(i).col);
            pg.vertex(p.x, p.y, p.z);
        }
        pg.endShape();

        popTransform(pg);
    }

    // End class 
}