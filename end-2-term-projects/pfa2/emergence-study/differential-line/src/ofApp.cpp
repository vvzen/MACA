#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    evolve = false;

    // 1. generate equally spaced points on a circle
    float radius = 16;
    int num_points = 16;
    float increment = 2*PI / num_points;

    cout << "creating nodes" << endl;

    for (float i = 0; i < PI*2; i+=increment){

        float x = cos(i) * radius;
        float y = sin(i) * radius;

        nodelist.append_node(ofPoint(x, y));
    }

    cout << "nodes.size(): " << nodelist.size() << endl;
    
    // build the line required to draw the connected points
    // nodelist.build_line();

    cam.setDistance(30);
    cam.setNearClip(0.5);
    cam.setFarClip(5000);

    glPointSize(4);
}

//--------------------------------------------------------------
void ofApp::update(){

    if (evolve){
        nodelist.grow();
        nodelist.differentiate();
        // nodelist.build_line();
    }

    evolve = false;
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(255);

    cam.begin();

    ofDrawAxis(10);

    ofSetColor(0);

    // ofPolyline * polyline = nodelist.get_line_ptr();
    // polyline->draw();

    nodelist.draw(true, true);

    cam.end();

    ofDrawBitmapString("nodelist.size(): " + ofToString(nodelist.size()), 20, 20);
}

//--------------------------------------------------------------
void ofApp::offset_points(){
    
    /* // float min_threshold = 5;
    float max_threshold = 50;

    int num_attempts = 0;

    // 2. space those points apart until a certain threshold
    
    for (int i = 0; i < nodes.size(); i++){

        // cout << "\nnew point!\n" << endl;
        // 2.1 move each point untill it reaches a set distance from its neighbours

        ofPoint * current_p = &nodes.at(i).pos;
        // ofPoint current_pos_val = nodes.at(i).pos;

        bool point_is_fine = false;

        while (num_attempts < 100 && !point_is_fine){

            // 2.1.1. move the point of a random quantity in a certain direction
            ofVec2f random_dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
            random_dir.normalize();
            random_dir *= ofRandom(5);
            current_p->x += random_dir.x;
            current_p->y += random_dir.y;

            // 2.1.2 find the 2 closest points to this one
            // TODO: optimize with a quadtree
            std::vector <Node> closest_nodes(nodes);

            // sort the points vector based on their distance from the current point
            // (sort lambda syntax taken from week 15 of wcc, see: https://stackoverflow.com/questions/32634239/c-sort-vector-based-on-distance-to-external-point)
            std::sort(closest_nodes.begin(), closest_nodes.end(), [current_p](const Node& node1, const Node& node2){
                return ofDist(current_p->x, current_p->y, node1.pos.x, node1.pos.y) < ofDist(current_p->x, current_p->y, node2.pos.x, node2.pos.y);
            });

            // 2.1.2 check if the 2 neighbour points are still inside our threshold values for min and max distance
            ofPoint neighbour_1 = closest_nodes.at(1).pos;
            ofPoint neighbour_2 = closest_nodes.at(2).pos;
            float neightbour_1_dist = ofDist(current_p->x, current_p->y, neighbour_1.x, neighbour_1.y);
            float neightbour_2_dist = ofDist(current_p->x, current_p->y, neighbour_2.x, neighbour_2.y);
            
            // cout << "\tmax_threshold: " << max_threshold << endl;
            // cout << "\tneightbour_1_dist: " << neightbour_1_dist << endl;
            // cout << "\tneightbour_2_dist: " << neightbour_2_dist << endl;

            // 2.1.3 if they're fine (within our threshold), go on with the next point
            // otherwise repeat this process
            if ((neightbour_2_dist < max_threshold) && (neightbour_1_dist < max_threshold)){
                    point_is_fine = true;
            }
            else {
                num_attempts++;
                // remove the random dir in order to reset it 
                current_p->x -= random_dir.x;
                current_p->y -= random_dir.x;
            }

            // 3. add a new point if the distance with the current one is half of the threshold
            if (neightbour_1_dist > max_threshold/2){
                
                Node added_node;
                ofPoint mid_position = current_p->getInterpolated(neighbour_2, 0.5);
                added_node.pos = ofPoint(mid_position.x, mid_position.y);

                cout << "\n------------------" << endl;
                cout << "adding a new point" << endl;

                // don't update anything if this is the last node
                // FIXME: find a way to loop to the beginning the graph
                if (i < nodes.size()-1){
                    
                    // update the connection graph
                    Node * next_node = &nodes.at(i+1);

                    added_node.previous_pos = *current_p;
                    next_node->previous_pos = added_node.pos;
                    nodes.push_back(added_node);
                    
                    cout << "added_node.pos:          " << added_node.pos << endl;
                    cout << "added_node.previous_pos: " << added_node.previous_pos << endl;
                    cout << "next_node.pos:  " << next_node->pos << endl;
                    cout << "next_node.pos: " << next_node->previous_pos << endl;
                }
            }
            // if (neightbour_2_dist > max_threshold/2){
                
            //     Node added_node;
            //     ofPoint mid_position = current_p->getInterpolated(neighbour_2, 0.5);
            //     added_node.pos = ofPoint(mid_position.x, mid_position.y);

            //     // mesh.addVertex(added_node.pos);

            //     // don't update anything if this is the last node
            //     // FIXME: find a way to loop to the beginning the graph
            //     if (i < nodes.size()-1){
                    
            //         // update the connection graph
            //         Node * next_node = &nodes.at(i+1);
 
            //         added_node.previous_pos = current_pos_val;
            //         next_node->previous_pos = added_node.pos;
            //         nodes.push_back(added_node);
            //     }
            // }
            
            // cout << "num_attempts: " << num_attempts << endl;
        }
    } */

    // 3. smooth the resulting path

    // 4. restart again by resampling


    // INCONVERGENT APPROACH
    // 2. randomly insert new nodes between pairs of existing points

    // 3. optimize the position of the nodes so they're not too close or too distant

}

//--------------------------------------------------------------
void ofApp::offset_points_var_a(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    evolve = true;

    // for (int i = 0; i < points.size(); i++){

    //     ofPoint *new_p;
    //     new_p = &points.at(i);
    //     new_p->y += 10;

    //     mesh.setVertex(i, *new_p);
    // }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    evolve = false;

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    offset_points();
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
