#include "ofMain.h"
#include <random>

//--------------------------------------------------------------
// Inspired by Inconvergent's Sand Spline, even if his is way more awesome
// (http://inconvergent.net/generative/sand-spline/)
//--------------------------------------------------------------

struct Grain {
	ofPoint pos;
	ofColor col;
	float size;
};

class SandLine {

    public:

        void setup(float w, float h, float max_size, float max_alpha);
        void update();
        void add_point(ofVec3f p, int max_offset, int max_radius);
        ofFbo * get_fbo_pointer();
        void set_target(ofVec2f target);
        void set_mode(int mode);
        void enable_draw(bool val);
        void reset(); // used after saving an artwork

        ofFbo fbo;
        int current_mode;
        // used in bezier mode
        deque <Grain> sand_grains;
        deque <ofPoint> main_sand_points;
        // used in attractor mode
        ofPoint latest_target;
        ofVec2f acceleration, velocity, position;

        // drawing modes
        static const int BEZIER_MODE = 1;
        static const int ATTRACTOR_MODE = 2;

        // for getting gaussian distribution
        std::default_random_engine generator;

    private:
        bool _enable_draw;
        float _max_size, _max_alpha;
};
