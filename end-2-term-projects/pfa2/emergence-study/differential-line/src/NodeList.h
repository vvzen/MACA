#include "ofMain.h"

// A point in space connected to another point
class Node {

	public:

		ofPoint pos;
		Node * next;
        int id;

		Node(){
            pos = ofPoint(0, 0, 0);
		}
		
        Node(ofPoint p){
            pos = p;
        }

        Node(ofPoint p, int index){
            pos = p;
            id = index;
        }
};

// A linked list responsible for adding nodes
// and creating a ofPolyline used to connect and draw them
class NodeList {

	public:

		Node * head;
		Node * tail;

		int nodes_count;
        // ofPolyline line;

        float min_distance = 40;
        float max_distance = 60;
        float subdivide_threshold = max_distance / 2;

        //--------------------------------------------------------------
		NodeList(){
			head = NULL;
			tail = NULL;
			nodes_count = 0;
            // line.clear();
		}

        ~NodeList(){

            Node * next = head;
            
            // iterate over all elements and free them
            while(next != NULL) {
                Node * to_be_deleted = next;
                // save pointer to the next element
                next = next->next;
                // delete the current entry
                delete to_be_deleted;
            }
        }

        //--------------------------------------------------------------
		void print_list(){
			
			cout << "print_list()" << endl;
			Node * current;
            current = head;

			while (current != NULL){
				cout << "\tnode id: " << current->id << endl;
				current = current->next;
			}
		}

        //--------------------------------------------------------------
		void append_node(ofPoint point){
			
			// cout << "append_node()" << endl;
			
            Node * node = new Node(point, nodes_count+1);
            node->next = NULL;

			if (head == NULL){
				// cout << "adding first element! " << node->id << endl;
                head = node;
                tail = node;
			}
			else {
				// cout << "\tadding new node: " << node->id << endl;
				// cout << "\tprevious tail:   " << tail->id << endl;
				// cout << "\tcurrent head:    " << head->id << endl;
				tail->next = node;
				tail = tail->next;
			}
            // line.addVertex(node->pos);
            // line.close();
			nodes_count++;
		}

        //--------------------------------------------------------------
		void insert_node(ofPoint point, int target_index){

			// cout << "insert_node() at index: " << target_index << endl;

            if (target_index == 0 && nodes_count == 0){
                append_node(point);
			}
            else {
                
                Node * new_node = new Node(point, nodes_count + 1);

                Node * current = head;
                int current_index = 0;

                while (current_index < target_index-1){

                    // cout << "\tcurrent index: " << current_index << endl;
                    // cout << "\tcurrent node:  " << current->id << endl;
                    
                    if (current->next != NULL){
                        current = current->next;
                        current_index++;
                    }
                    else {
                        // cout << "\treached end of the nodelist, index is greater of number of current nodes" << endl;
                        // cout << "\tcurrent nodes: " << nodes_count << ", index given: " << target_index << endl;
                        break;
                    }
                }
                // cout << "\tinserting " << new_node->id << endl;
                Node * tmp = current->next;
                current->next = new_node;
                new_node->next = tmp;

                // line.insertVertex(new_node->pos, target_index);
                nodes_count++;
            }
		}

        //--------------------------------------------------------------
        void draw(bool draw_vertices, bool draw_line){

            cout << "draw()" << endl;

            // line.clear();

            Node * current = head;

            ofVboMesh vertices_mesh;
            vertices_mesh.setMode(OF_PRIMITIVE_POINTS);
            ofMesh lines_mesh;
            lines_mesh.setMode(OF_PRIMITIVE_LINE_LOOP);

            while (current != NULL){

                if (draw_vertices) vertices_mesh.addVertex(current->pos);
                if (draw_line) lines_mesh.addVertex(current->pos);

                current = current->next;
            }

            if (draw_vertices) vertices_mesh.draw();
            if (draw_line) lines_mesh.draw();

            // line.addVertex(ofPoint(current->pos));
            // line.close();
        }
        
        //--------------------------------------------------------------
        // Randomly introduce new nodes between pairs of existing nodes
        //--------------------------------------------------------------
        void grow(){

            Node * current = head;

            int i = 0;
            // loop inside the points
            while (current != NULL){

                // 1 check if the next point is still inside our threshold values for min and max distance
                float distance;
                
                if (current->next != NULL){
                    distance = ofDist(current->pos.x, current->pos.y, current->next->pos.x, current->next->pos.y);
                }
                else {
                    distance = ofDist(current->pos.x, current->pos.y, head->pos.x, head->pos.y);
                }
                // cout << "distance: " << distance << endl;

                // 2. add a new if distance is over threshold
                if (ofRandom(1.0) > 0.97){
                // if (distance > subdivide_threshold){
                    
                    // cout << "list before inserting" << endl;
                    // print_list();

                    ofPoint mid_position;
                    
                    if (current->next != NULL){
                        mid_position = current->pos.getInterpolated(current->next->pos, 0.5);
                    }
                    else {
                        mid_position = current->pos.getInterpolated(head->pos, 0.5);
                    }
                    mid_position += ofVec2f(ofRandom(-0.3, 0.3), ofRandom(-0.3, 0.3));
                    insert_node(mid_position, i+1);
                }

                i++;
                // go to the next point
                current = current->next;
            }

            // build_line();
        }

        //--------------------------------------------------------------
        // Push points apart if they're too close
        // From inconvergent's website:
        // They want to be close, but not too close, to their two neighbors. 
        // At the same time they want to be as far away as possible from all
        // other nodes within a certain distance.
        //--------------------------------------------------------------
        void differentiate(){

            //TODO: push nodes apart if their distance is too low

            Node * current = head;

            // 1. loop inside each point
            while (current != NULL){
                
                Node * current_inner = head;
                
                // 2. and loop inside every other point
                while (current_inner != NULL){
                    
                    float distance = ofDist(current->pos.x, current->pos.y, current_inner->pos.x, current_inner->pos.y);
                    
                    float distance_of_interest = max_distance * 4;

                    if (distance < distance_of_interest){

                        // 3. check if the distance is lower than our min threshold
                        if (distance <= min_distance){
                            
                            // 3.1 move the point away
                            ofVec2f repulsion_force = current->pos - current_inner->pos;
                            // repulsion_force.normalize();
                            repulsion_force *= 0.01;
                            current->pos += repulsion_force;
                        }


                        // 4. check if the distance is greater than our max threshold 
                        if (distance > max_distance){
                            
                            // 3.2 move the point closer
                            ofVec2f attraction_force = current_inner->pos - current->pos;
                            // attraction_force.normalize();
                            attraction_force *= 0.01;
                            current->pos += attraction_force;
                        }
                    }


                    current_inner = current_inner->next;
                }

                current = current->next;
            }
        }

        //--------------------------------------------------------------
        // ofPolyline * get_line_ptr(){
        //     return &line;  
        // }        

        //--------------------------------------------------------------
        int size(){
            return nodes_count;
        }
};