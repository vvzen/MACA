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
            // int alt = row.getString("argos:altitude");

            String id = row.getString("tag-local-identifier");
            String name = row.getString("individual-taxon-canonical-name");

            if (id.equals("126694")){
                println("id: " + id + ", name: " + name + ", lat,lon: " + lat + ", " + lon);
                PVector pos = sphericalToCartesian(lat, lon, 1.0);
            }
        }

    }

    // overriding from super
    public void setup(){
        
    }

    public void update(){

    }

    // see https://en.wikipedia.org/wiki/Spherical_coordinate_system
    PVector sphericalToCartesian(float lat, float lon, float radius){
    
        float latitude = radians(lat);
        float longitude = radians(lon);

        float x = radius * sin(latitude) * cos(longitude);
        float y = radius * sin(latitude) * sin(longitude);
        float z = radius * cos(latitude);

        return new PVector(x, y, z);
    }

    // End class 
}