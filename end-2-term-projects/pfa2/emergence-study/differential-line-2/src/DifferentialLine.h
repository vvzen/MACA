#include "ofMain.h"
#include "Node.h"
#include "globals.h"

class DifferentialLine {

    public:
        vector <Node *> nodes;
        ofMesh lines_mesh;

        DifferentialLine(){
            lines_mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
        }
        
        ~DifferentialLine(){
            for (int i = 0; i < nodes.size(); i++){
                Node * node = nodes.at(i);
                delete node;
            }
        }

        void add_node(Node * n);
        void add_node_at(Node * n, int index);
        void grow();
        void differentiate();
        void draw(bool lines, bool vertices);
        void reset();

};