#include "ofMain.h"
#include <random>

struct Grain {
	ofPoint pos;
	ofColor col;
	float size;
};

class SandLine {

    public:

        void setup(float w, float h, float max_size, float max_alpha);
        void update();
        void add_point(ofVec3f p);
        ofFbo * get_fbo_pointer();
        
        void enable_draw(bool val);

        ofFbo fbo;
        deque <Grain> sand_grains;
        deque <ofPoint> main_sand_points;
        int points_added;

        // for getting gaussian distribution
        std::default_random_engine generator;
        bool _enable_draw;

    private:
        float _max_size, _max_alpha;
};
