#include "ofMain.h"

class FireworkParticle {

    public:

        void setup(ofPoint pos, ofVec3f vel, bool is_initial=false);
        void update();
        void apply_force(ofVec3f force);
        bool is_active();
        void set_active(bool val);
        bool is_initial();

        ofPoint position;
        ofVec3f acceleration, velocity;
        ofVec3f size;
        float lifespan; // expectancy of life, in millis
        float start_time, current_lifetime; // millis

    private:
        bool _is_active;
        bool _is_initial;
};