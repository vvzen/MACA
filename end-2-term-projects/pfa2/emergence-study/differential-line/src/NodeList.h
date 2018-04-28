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
        ofPolyline line;

        //--------------------------------------------------------------
		NodeList(){
			head = NULL;
			tail = NULL;
			nodes_count = 0;
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
			
			cout << "append_node()" << endl;
			
            Node * node = new Node(point, nodes_count+1);
            node->next = NULL;

			if (head == NULL){
				cout << "adding first element! " << node->id << endl;
				
                head = node;
                tail = node;
			}
			else {
				cout << "\tadding new node: " << node->id << endl;
				cout << "\tprevious tail:   " << tail->id << endl;
				cout << "\tcurrent head:    " << head->id << endl;
				tail->next = node;
				tail = tail->next;
			}
			nodes_count++;
		}

        //--------------------------------------------------------------
		void insert_node(ofPoint point, int target_index){

			cout << "insert_node() at index: " << target_index << endl;

            if (target_index == 0 && nodes_count == 0){
                append_node(point);
			}
            else {
                
                Node * new_node = new Node(point, nodes_count + 1);

                Node * current = head;
                int current_index = 0;

                while (current_index < target_index-1){

                    // cout << "\tcurrent index: " << current_index << endl;
                    cout << "\tcurrent node:  " << current->id << endl;
                    
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
                cout << "\tinserting " << new_node->id << endl;
                Node * tmp = current->next;
                current->next = new_node;
                new_node->next = tmp;
                
                nodes_count++;
            }
		}

        //--------------------------------------------------------------
        void build_line(){

            cout << "build_line()" << endl;

            line.clear();

            Node * current = head;

            while (current->next != NULL){
                cout << "\tcurrent node:  " << current->id << endl;
                line.addVertex(ofPoint(current->pos));
                current = current->next;
            }
            line.addVertex(ofPoint(current->pos));
            line.close();
        }
        
        //--------------------------------------------------------------
        // Spaces points apart until a certain threshold
        //--------------------------------------------------------------
        void grow_points(){

            // float min_threshold = 5;
            float max_distance = 40;

            Node * current = head;

            int i = 0;
            // loop inside the points
            while (current->next != NULL){

                int num_attempts = 0;

                // 2.1 move each point until it reaches a set distance from its next point
                bool point_is_fine = false;

                // 2.1.1. move the point of a random quantity in a certain direction
                ofVec2f random_dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
                random_dir.normalize();
                random_dir *= ofRandom(20);
                current->pos.x += random_dir.x;
                current->pos.y += random_dir.y;

                // 2.1.2 check if the next point is still inside our threshold values for min and max distance
                float distance = ofDist(current->pos.x, current->pos.y, current->next->pos.x, current->next->pos.y);
                cout << "distance: " << distance << endl;

                // 3. add a new point if the distance is greater than our threshold
                if (distance > max_distance){
                    
                    cout << "list before inserting" << endl;
                    print_list();

                    ofPoint mid_position = current->pos.getInterpolated(current->next->pos, 0.5);
                    cout << "inserting node with id: " << nodes_count + 1 << endl;
                    
                    insert_node(mid_position, i+1);
                    
                    // cout << "list after inserting" << endl;
                    // print_list();

                    build_line();
                }

                i++;
                // go to the next point
                current = current->next;
            }
        }

        //--------------------------------------------------------------
        ofPolyline * get_line_ptr(){
            return &line;  
        }        

        //--------------------------------------------------------------
        int size(){
            return nodes_count;
        }
};