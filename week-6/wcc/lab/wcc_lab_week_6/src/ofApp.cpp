#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // get a list of devices
    vector<ofVideoDevice> devices = vid_grabber.listDevices();

    for (int i = 0; i < devices.size(); i++){
        if (devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }
        else {
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    num_of_tiles = 5;
    vid_grabber.setDeviceID(0);
    vid_grabber.setDesiredFrameRate(30);
    vid_grabber.initGrabber(320, 240);
    max_buffer_size = pow(num_of_tiles, 2);

    tile_size_x = ofGetWidth() / num_of_tiles;
    tile_size_y = ofGetHeight() / num_of_tiles;

    cout << "tile_size_x: " << tile_size_x << endl;
    cout << "tile_size_y: " << tile_size_y << endl;

    // font
    loading_text = "Loading.";
    gotham.load("fonts/Andale-Mono.ttf", 28);

    ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){

    vid_grabber.update();

    if (vid_grabber.isFrameNew()){
        // add to buffer
        ofImage img;
        img.setFromPixels(vid_grabber.getPixels());
        img.mirror(false, false); // if you want to mirror input
        img_buffer.push_front(img); // add image to front of the queue
    }

    // remove from back if buffer has reached maximum size
    if (img_buffer.size() > max_buffer_size) img_buffer.pop_back();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    int image_index = 0;

    ofSetColor(255);
    // wait for the buffer to be filled with all the images
    if (img_buffer.size() == max_buffer_size){
        // draw the array of images
        for (int y = 0; y < num_of_tiles; y++){
            for (int x = 0; x < num_of_tiles; x++){
                
                ofPoint current_pos = ofPoint(x * tile_size_x, y * tile_size_y);

                // ofSetColor(ofMap(x, 0, num_of_tiles, 120, 255), ofMap(y, 0, num_of_tiles, 120, 255), 255);
                img_buffer[image_index].draw(current_pos);
                image_index++;
            }
        }
    }
    else {
        ofBackground(30);
        ofSetHexColor(0xEA1C2E);

        ofRectangle font_bb = gotham.getStringBoundingBox("Loading..", ofGetWidth()/2, ofGetHeight()/2   );
        if(ofGetFrameNum() % 25 == 0){
            loading_text = "Loading.";
        }
        else if (ofGetFrameNum() % 33 == 0){
            loading_text = "Loading..";
        }
        else if (ofGetFrameNum() % 41 == 0){
            loading_text = "Loading...";
        }
        else if (ofGetFrameNum() % 47 == 0){
            loading_text = "Loading...";
        }
        gotham.drawString(loading_text, ofGetWidth()/2 - font_bb.width/2, ofGetHeight()/2 - font_bb.height/2);

        // ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);

        // ofDrawBitmapString("Loading..", ofGetWidth()/2 - 20, ofGetHeight()/2, 0);
        // ofDrawBitmapString(ofToString(img_buffer.size()) + "/100", ofGetWidth()/2 - 20, ofGetHeight()/2 + 20, 0);
        cout << "size of img buffer: " << img_buffer.size() << endl;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
