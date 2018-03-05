public class ImageReader extends Plane {

    PImage img;

    ImageReader(){
        super();
    }

    // SETUP
    // override setup function to create a plane
    public void setup(){
        vertices = new ArrayList<Vert>();

        img = loadImage("tst.png");
        img.loadPixels();

        wid = img.width;
        hei = img.height;
        scl = 10;

        for(int i = 0; i < wid; i++){
            for(int j = 0; j < hei; j++){
                pushVert(i*scl - (wid*scl/2.0),
                        j*scl - (hei*scl/2.0),
                        getZAt(i, j, wid));
            }
        }

        //img.updatePixels();
    }


    float getZAt(int i, int j, int w){
        float res = brightness(img.pixels[i + j * w]);
        res *= 0.01 * param_D;
        return res;
    }

}