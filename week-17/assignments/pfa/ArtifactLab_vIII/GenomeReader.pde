public class GenomeReader extends Artifact{

    String[] lines;
    PVector plotPos; // represents current position
    int lineCounter;

    // scale - this controls the resolution of the final print
    float unit = 0.5;
    // counter vars
    int start = 1;
    int end = 19999;

    // Constructor
    GenomeReader(){
        super();

        // get the data as an array of strings
        lines = loadStrings("hs_alt_CHM1_1.1_chr1.mfa");
        lineCounter = 1;
    }

    // overriding from super
    public void setup(){
        vertices = new ArrayList<Vert>();
        plotPos = new PVector(0,0,0);
    }

    public void update(){

        if(lineCounter < 2000){
            // read through a line and add vertices accordingly
            String currLine = lines[lineCounter];

            //println(currLine.length());
            //println(currLine.charAt(0));

            for (int i = 0; i < currLine.length(); i++) {

                char c = currLine.charAt(i);
                
                // add a vertex depending on what c is
                plotPos.add(mapPos(c));
                // plotPos.z += sin(i) * lineCounter;
                pushVert(plotPos);
            }
            lineCounter++;
        }
    }

    // simple switch statement that maps a char to a direction vector
    PVector mapPos(char c) {
        
        PVector res = new PVector(0, 0, 0);
        switch(c) {
        case 'n':
        case 'N':
            // res.add(new PVector(-unit, -unit));
            // blank - do nothing
            break;
        case 'a':
        case 'A':
            if (floor(random(2)) == 0){
                res.x += unit;
            }
            else {
                res.x -= unit;
            }
            // res.rotate(HALF_PI);
            break;
        case 'g':
        case 'G':
            if (floor(random(2)) == 0){
                res.y += unit;
            }
            else {
                res.y -= unit;
            }
            // res.rotate(-HALF_PI);
            break;
        case 't':
        case 'T':
            if (floor(random(2)) == 0){
                res.z += unit;
            }
            else {
                res.z -= unit;
            }
            // res.rotate(PI);
            break;
        case 'c':
        case 'C':
            // res.x += unit;
            // res.rotate(-PI);
            // res.add(new PVector(-unit, 0));
            break;
        }
        return res;
    }
    // End class 
}