#include "ofMain.h"

class Snake {
    public:

        deque <ofPoint> snakePoints;
        void addLocation(int x, int y);
        void setup(ofColor c);
        void draw();

        ofColor target_c;
};