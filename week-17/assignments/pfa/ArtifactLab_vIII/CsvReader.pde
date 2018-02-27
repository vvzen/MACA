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
        table = loadTable("cuckoos.csv", "header");
        println(table.getRowCount() + " total rows in table");

        vertices = new ArrayList<Vert>();

        // loop through dataset
        for (TableRow row : table.rows()) {
    
            float lat = row.getFloat("location-lat");
            float lon = row.getFloat("location-long");
            // float alt = row.getFloat("argos:altitude");

            String id = row.getString("tag-local-identifier");
            String name = row.getString("individual-taxon-canonical-name");

            if (id.equals("126694")){
                println("id: " + id + ", name: " + name + ", lat,lon: " + lat + ", " + lon);
                // PVector pos = sphericalToCartesian(lat, lon, 6371);
                PVector pos = sphericalToCartesian(lat, lon, 1000);
                // pos.mult(0.1);
                pushVert(pos);
            }
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
        
        //draw all vertices
        pg.beginShape(POINTS);
        for(int i = 0; i < vertices.size();i++){
            PVector p = vertices.get(i).position;
            pg.vertex(p.x, p.y, p.z);
        }
        pg.endShape();

        popTransform(pg);
    }

    // End class 
}