#include "Firework.h"

//--------------------------------------------------------------
void Firework::setup(ofPoint pos, ofFloatColor col){
    position = pos;
    color = col;
    // give some initial y velocity to the first particle
    initial_particle.setup(pos, ofVec3f(0,0,1), true);

    // setup the mesh
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_POINTS);

    // reset everything
    particles.clear();
    _exploded = false;
    initial_particle.set_active(true);
    
    // this needs to be added to inside ofApp::setup()
    // ofLoadImage(firework.texture, "mytexture.png");
}

//--------------------------------------------------------------
void Firework::update(){

    if (initial_particle.is_active()){
        initial_particle.update();
    }
    else {
        // when the particle reaches the top
        if (!_exploded){

            for (int i = 0; i < 30; i++){
                FireworkParticle new_particle;
                new_particle.setup(
                    initial_particle.position,
                    ofVec3f(ofRandom(-0.35, 0.35), ofRandom(-0.35, 0.35), ofRandom(-0.35, 0.35))
                );
                
                particles.push_back(new_particle);
                // add particles to the mesh
                mesh.addVertex(ofVec3f(new_particle.position));
                mesh.addColor(color);
            }
            _exploded = true;
            // cout << "Firework::exploded!" << endl;
        }
        else {
            for (int i = 0; i < particles.size(); i++){

                if (particles.at(i).is_active()){
                    
                    particles.at(i).update();

                    // update the mesh vertices
                    ofVec3f p = mesh.getVertex(i);
                    p.x = particles.at(i).position.x;
                    p.y = particles.at(i).position.y;
                    p.z = particles.at(i).position.z;

                    mesh.setVertex(i, p);
                    // set alpha
                    float alpha = ofMap(particles.at(i).current_lifetime, 0, particles.at(i).lifespan, 1, 0, true);
                    mesh.setColor(i, ofFloatColor(color.r, color.g, color.b, alpha));
                }
                // when particle is dead, delete it
                else {
                    // int id = mesh.getVertex(i);
                    mesh.removeVertex(i);
                    particles.erase(particles.begin() + i);
                }
            }
        }
    }
}

//--------------------------------------------------------------
bool Firework::exploded(){
    return _exploded;
}