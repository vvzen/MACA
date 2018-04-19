#include "ofMain.h"
#include "FireworkParticle.h"

class Firework {

    public:

        void setup(ofPoint pos, ofFloatColor col);
        void update();
        bool exploded();

        // physics
        FireworkParticle initial_particle;
        vector <FireworkParticle> particles;
        ofVec3f position;
        // shading
        ofColor color;
        ofMesh mesh;
		ofTexture texture;
    
    private:
        bool _exploded;
};