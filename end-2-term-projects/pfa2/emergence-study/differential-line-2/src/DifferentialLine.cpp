#include "DifferentialLine.h"

//--------------------------------------------------------------
void DifferentialLine::add_node(Node * n){
    nodes.push_back(n);
}

//--------------------------------------------------------------
void DifferentialLine::add_node_at(Node * n, int index){
    nodes.insert(nodes.begin() + index, n);
}

//--------------------------------------------------------------
void DifferentialLine::grow(){

    for (int i = 0; i < nodes.size(); i++){
        
        Node * node_1 = nodes.at(i);
        Node * node_2;

        // if this is the body of the list
        if (i != nodes.size()-1){
            node_2 = nodes.at(i+1);
        }
        // if this is the tail of the list
        else {
            node_2 = nodes.at(0);
        }

        float distance = node_1->pos.distance(node_2->pos);
        // cout << "edge length: " << distance << endl;
        
        if (distance > MAX_EDGE_LENGTH && nodes.size() < MAX_NODES_NUM){
            // int index = nodes.find(n2);
            ofVec2f mid_position = node_1->pos.getInterpolated(node_2->pos, 0.5f);
            
            Node * new_node = new Node(mid_position);
            nodes.insert(nodes.begin()+i+1, new_node);
        }
    }
}

//--------------------------------------------------------------
void DifferentialLine::differentiate(){

    for (int i = 0; i < nodes.size(); i++){
        Node * node = nodes.at(i);
        node->update(nodes);
    }
}

//--------------------------------------------------------------
void DifferentialLine::draw(bool lines, bool vertices){

    lines_mesh.clear();

    ofMesh points_mesh;
    points_mesh.setMode(OF_PRIMITIVE_POINTS);

    for (int i = 0; i < nodes.size(); i++){
        Node * node = nodes.at(i);
        if (lines) lines_mesh.addVertex(node->pos);
        if (vertices) points_mesh.addVertex(node->pos);
    }

    if (lines) lines_mesh.draw();
    if (vertices) points_mesh.draw();
}

//--------------------------------------------------------------
void DifferentialLine::reset(){

    nodes.clear();
}