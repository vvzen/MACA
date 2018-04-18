#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackgroundHex(0x000000);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);

    firework.setup(ofVec3f(0,0,0), ofColor(255, 10, 50));
    
    // fireworks.push_back(firework);

    cam.setDistance(300);

    cam.setNearClip(2);
    cam.setFarClip(15000);

    firework_mesh.clear();
    firework_mesh.setMode(OF_PRIMITIVE_POINTS);
    for (int i = 0; i < 30; i++){
        ofVec3f p = ofVec3f(ofRandom(0, 20), ofRandom(0, 20), ofRandom(0, 20));
        firework_mesh.addVertex(p);
        firework_mesh.addColor(ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
    }
    // don't use the normal gl texture
	ofDisableArbTex();
	// load the texture for the particles
    ofLoadImage(firework.texture, "dot.png");
    
    glPointSize(16);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    firework.update();

    cout << "firework.particles.size(): " << firework.particles.size() << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0, 0, 0);

    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnablePointSprites();

    cam.begin();

    ofDrawAxis(100);

    if (!firework.exploded()){
        ofDrawSphere(
            firework.initial_particle.position.x,
            firework.initial_particle.position.y,
            firework.initial_particle.position.z,
            1);
    }
    else {
        for (int p =0; p < firework.particles.size(); p++){
            // ofDrawSphere(
            //     firework.particles.at(p).position.x,
            //     firework.particles.at(p).position.y,
            //     firework.particles.at(p).position.z,
            //     2);
        }
        // texture.bind();
        firework.texture.bind();
        // firework_mesh.draw();
        firework.mesh.draw();
        firework.texture.unbind();
    }

    cam.end();

    ofDisablePointSprites();
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

    // Firework firework;
    // firework.setup(ofVec3f(0,0,0));
    // fireworks.push_back(firework);
    
    // if (fireworks.size() > 5){
    //     fireworks.pop_front();
    // }

    firework.setup(ofVec3f(0,0,0), ofColor(255, 10, 50));
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
