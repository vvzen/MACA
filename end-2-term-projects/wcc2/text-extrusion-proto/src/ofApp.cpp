#include "ofApp.h"

// TODO:
// create a word at the center of the screen in 3d mode
// get the contour points (2d shape)
// copy them and move them on the z axis
// repeat a few times
// add all of those points to an ofMesh
// draw it and see what happens

//--------------------------------------------------------------
void ofApp::setup(){

    font.load("fonts/AndaleMono.ttf", 40, true, true, true);

    cam.setDistance(100);
    key_light.setPointLight();

    ofSetSphereResolution(60);

    extrusion_depth = 10;

    ///////////////////
    // START DRAWING //
    ///////////////////

    current_word =  "openframeworks";
    
    word_bb = font.getStringBoundingBox(current_word, 0, 0);
    
    test_meshes = extrude_mesh_from_text(current_word, font, extrusion_depth);

    /* vector <ofPath> word_paths = font.getStringAsPoints(current_word, 0, 0);

    // FUCK YEAH!
    // create the front mesh using a temporary ofPath and then extract its tessellation
    for (int i = 0; i < word_paths.size(); i++){

        // for every char break it into polyline
        // (simply a collection of the inner and outer points)
        vector <ofPolyline> char_polylines = word_paths.at(i).getOutline();

        ofVboMesh front; // the final vbo used to store the vertices
        ofPath front_path; // a temp path used for computing the tessellation of the 2d shape

        // First loop is for each polyline
        // see http://openframeworks.cc/documentation/graphics/ofTrueTypeFont/#show_getStringAsPoints
        for (int c = 0; c < char_polylines.size(); c++){
            // Second loop is for each point on the polyline
            for (int p = 0; p < char_polylines[c].size(); p++){

                if (p == 0){
                    front_path.moveTo(char_polylines[c][p]);
                }
                else {
                    front_path.lineTo(char_polylines[c][p]);
                }
            }
        }
        front = front_path.getTessellation();
        front_meshes.push_back(front);
    }

    // make the extruded sides
    for (int i = 0; i < word_paths.size(); i++){
        vector <ofPolyline> lines = word_paths.at(i).getOutline();
        for (int j = 0; j < lines.size(); j++){
            
            ofVboMesh side;
            vector <ofPoint> points = lines.at(j).getVertices();
            int k = 0;

            for (k = 0; k < points.size()-1; k++){
                ofPoint p1 = points.at(k+0);
                ofPoint p2 = points.at(k+1);

                side.addVertex(p1);
                side.addVertex(p2);
                side.addVertex(ofPoint(p1.x, p1.y, p1.z+extrusion_depth));
                side.addVertex(ofPoint(p2.x, p2.y, p2.z+extrusion_depth));
                side.addVertex(p2);
            }

            // connect the last to the first
            ofPoint p1 = points.at(k);
            ofPoint p2 = points.at(0);
            side.addVertex(p1);
            side.addVertex(p2);
            side.addVertex(ofPoint(p1.x, p1.y, p1.z+extrusion_depth));
            
            side.addVertex(ofPoint(p1.x, p1.y, p1.z+extrusion_depth));
            side.addVertex(ofPoint(p2.x, p2.y, p2.z+extrusion_depth));
            side.addVertex(p2);

            side.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

            word_meshes.push_back(side);
        }
    } */
}

//--------------------------------------------------------------
void ofApp::update(){

    current_offset = ofMap(mouseX, 0, ofGetWidth(), 5, 1); // depth between front and back faces
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofEnableDepthTest();

    ofBackground(0);
    ofFill();

    // enable lights
    key_light.lookAt(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0), ofVec3f(0, 1, 0));
    float x, z;
    float y = 30;
    float radius = 30;
    x = cos(ofGetElapsedTimeMillis() * 0.001) * radius;
    z = sin(ofGetElapsedTimeMillis() * 0.001) * radius;
    
    cam.begin();

    ofDrawSphere(x, y, z, 5);

    key_light.setGlobalPosition(x, y, z);
    key_light.enable();
    
    // stuff for reference
    // ofDrawGrid();
    // ofDrawSphere(0, 0, 0, 5);

    ofPushMatrix();

    // ofTranslate(60, ofGetHeight() / 2);
    // ofRotateX(ofGetFrameNum() * 3);
    ofScale(0.12, 0.12, 0.12);
    ofTranslate(-word_bb.width / 2, - word_bb.height / 2);
    
	ofFill();
    ofScale(1, -1, 1); // flip y axis

    // for (int m = 0; m < test_meshes.size(); m++){
    for (int m = 0; m < test_meshes.size(); m++){
        test_meshes.at(m).draw();
    }

    // draw all side meshes
    // for (int m = 0; m < word_meshes.size(); m++){
    //     ofPushMatrix();
    //     ofTranslate(0, 0, current_offset);
    //     word_meshes.at(m).draw();
    //     ofPopMatrix();
    // }
    // // draw all front and back paths
    // for (int f = 0; f < front_meshes.size(); f++){
    //     ofPushMatrix();
    //     ofTranslate(0, 0, current_offset);
    //     front_meshes.at(f).draw();
    //     ofTranslate(0, 0, extrusion_depth);
    //     front_meshes.at(f).draw();
    //     ofPopMatrix();
    // }

    ofPopMatrix();

    cam.end();

    key_light.disable();

   ofDisableDepthTest();
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
