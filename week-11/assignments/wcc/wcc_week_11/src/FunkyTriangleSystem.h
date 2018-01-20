#include "ofMain.h"
#include "ofxDelaunay.h"
#include "FunkyTriangle.h"

class FunkyTriangleSystem {

    public:
        
        void setup();
        vector<ofPoint> get_triangle_points(ofxDelaunay & triangulation, int index);
        void add_triangle(FunkyTriangle tri);
        int size();
        void clear();
        void update();
        void draw();

        vector <FunkyTriangle> tris_vector;
};