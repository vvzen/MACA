#include "ofApp.h"

//---------------------
void ofApp::setup(){
    vidGrabber.setDeviceID(0);

    cout << "video devices : " << endl;
    cout << vidGrabber.listDevices().size() << endl;
    // for (int i = 0; i < vidGrabber.listDevices().size(); i++){
    // }

    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640,480);
    rTarget = 255;
    gTarget = 182;
    bTarget = 193;
    threshold = 2.5;
}
//---------------------
void ofApp::update(){
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()){

        // these are used in the search for the location of the pixel
        // whose color is the closest to our target color.
        closestColorX = 0;
        closestColorY = 0;
        int w = vidGrabber.getWidth();
        int h = vidGrabber.getHeight();
        count = 0;

        for (int s = 0; s < snakes.size(); s++){

            for (int y=0; y<h; y++) {
                for (int x=0; x<w; x++) {
                    
                    // Extract the color components of the pixel at (x,y)
                    // from myVideoGrabber (or some other image source)
                    ofColor colorAtXY = vidGrabber.getPixels().getColor(x, y);
                    float rAtXY = colorAtXY.r;
                    float gAtXY = colorAtXY.g;
                    float bAtXY = colorAtXY.b;
                    
                    // float colorDistance = ofDist(rAtXY, gAtXY, bAtXY, rTarget, gTarget, bTarget);
                    float colorDistance = ofDist(rAtXY, gAtXY, bAtXY, snakes[s].target_c.r, snakes[s].target_c.g, snakes[s].target_c.b);
                    
                    //if color similar then add coordinates to sum
                    if(colorDistance < threshold){
                        closestColorX+= x;
                        closestColorY+= y;
                        count++;
                    }
                }
            }
            //calculate the average coordinate
            if (count>0) {
                closestColorX = closestColorX / count;
                closestColorY = closestColorY / count;
                snakes[s].addLocation(closestColorX, closestColorY);
            }
        }

    }
}

//---------------------
void ofApp::draw(){
    vidGrabber.draw(0,0);
    ofDrawBitmapString(threshold, 20, 20);
    // ofDrawEllipse (closestColorX, closestColorY, 40,40);

    snake.draw();
}
//---------------------
void ofApp::mousePressed(int x, int y, int button){
    ofColor tempColor = vidGrabber.getPixels().getColor(x, y);
    rTarget = tempColor.r;
    gTarget = tempColor.g;
    bTarget = tempColor.b;

    Snake new_snake;
    new_snake.setup(tempColor);
    snakes.push_back(new_snake);

    // make sure we just have 2 snakes at one time
    if (snakes.size() > 2){
        snakes.pop_front();   
    }
}
//-----------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_UP) threshold+=1;//UP ARROW
    else if (key==OF_KEY_DOWN) threshold-=1;//DOWN ARROW
}
