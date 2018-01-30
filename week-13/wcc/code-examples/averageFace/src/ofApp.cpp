#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	finder.setup("haarcascade_frontalface_default.xml");

    videoGrabber.setDeviceID(0);
    videoGrabber.setDesiredFrameRate(30);
    videoGrabber.initGrabber(640, 480);
    faceCounter=0;
    cvAvgImage.allocate(300,300);
    cvAvgImage.set(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    finder.setScaleHaar(1.1);
    videoGrabber.update();
    img.setFromPixels(videoGrabber.getPixels());
	finder.findHaarObjects(img);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofNoFill();
    img.draw(0, 0);

    if(videoGrabber.isFrameNew()){
        for(unsigned int i = 0; i < finder.blobs.size(); i++) { // loop over all the found faces/blobs
            cur = finder.blobs[i].boundingRect;     // and put a rectangle around the face
            ofDrawRectangle(cur);
            cvAvgImage.draw(mouseX, mouseY);
        }
    }

}

void ofApp::mousePressed(int x, int y, int button){
    faceCounter = 0;
    cvSumImage.allocate(300,300);
    cvSumImage.set(0);
    cvAvgImage.allocate(300,300);
    cvAvgImage.set(0);
}

void ofApp::keyPressed(int key){
        croppedImg.clone(img);
        croppedImg.crop(cur.x-50, cur.y-50, 300, 300);
        cvImg = croppedImg;
        cvGrayImage = cvImg;
        if (!cvSumImage.bAllocated){
            cvSumImage=cvGrayImage;
            faceCounter++;
        }
        else {
            cvFloatImg = cvGrayImage;
            cvSumImage+=cvFloatImg;
            faceCounter++;
            cvCounterImg.allocate(300,300);
            cvCounterImg.set(1./faceCounter);
            cvAvgImage = cvSumImage;
            cvAvgImage *= cvCounterImg;
        }
}
