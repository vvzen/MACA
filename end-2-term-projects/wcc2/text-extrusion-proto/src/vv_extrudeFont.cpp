#include "vv_extrudeFont.h"


//--------------------------------------------------------------
// Original credits go to jefftimeisten, see https://forum.openframeworks.cc/t/extrude-text-into-3d/6938
//
// This method returns a vector containing the vbo meshes required
// to render the front, back and sides of each character in the given string.
//
// @example:
//
// void ofApp::setup(){
       // my_extruded_word is a vector<ofVboMesh>
//     my_extruded_word = extrude_mesh_from_text(word, font, extrusion_depth);
// }
// 
// void ofApp::draw(){
//     for (int m = 0; m < my_extruded_word.size(); m++){
//         my_extruded_word.at(m).draw();
//     }
// }
//--------------------------------------------------------------
vector<ofVboMesh> extrude_mesh_from_text(string word, ofTrueTypeFont & font, float extrusion_depth){

    // contains all of the paths of the current word
    vector <ofPath> word_paths = font.getStringAsPoints(word, 0, 0);

    vector <ofVboMesh> front_meshes, back_meshes, side_meshes;

    // meshes for the sides and the front of the 3d extruded text
    vector<ofVboMesh> all_meshes; // returned meshese (sides + front + back)

    // loop through all the characters paths
    for (int i = 0; i < word_paths.size(); i++){

        ofVboMesh current_char_mesh;
        
        // 1. create the front mesh using a temporary ofPath and then extract its tessellation

        // for every char break it into polyline
        // (simply a collection of the inner and outer points)
        vector <ofPolyline> char_polylines = word_paths.at(i).getOutline();

        ofVboMesh front; // the final vbos used to store the vertices
        ofPath front_path; // a temp path used for computing the tessellation of the letter shape

        // now we build an ofPath using the vertices from the character polylines
        // first loop is for each polyline in the character
        // see http://openframeworks.cc/documentation/graphics/ofTrueTypeFont/#show_getStringAsPoints
        for (int c = 0; c < char_polylines.size(); c++){
            // second loop is for each point on the polyline
            for (int p = 0; p < char_polylines[c].size(); p++){

                if (p == 0){
                    front_path.moveTo(char_polylines[c][p]);
                }
                else {
                    front_path.lineTo(char_polylines[c][p]);
                }
            }
        }
        front = front_path.getTessellation();
        ofVec3f * front_vertices = front.getVerticesPointer();

        // compute the back by just offsetting the vertices of the required amount
        ofVboMesh back = front;

        for (int v = 0; v < front.getNumVertices(); v++){
            front_vertices[v].z += extrusion_depth;
        }

        current_char_mesh.append(front);
        current_char_mesh.append(back);

        all_meshes.push_back(current_char_mesh);

        // 2. make the extruded sides
        vector <ofPolyline> lines = word_paths.at(i).getOutline();
        for (int j = 0; j < lines.size(); j++){
            
            ofVboMesh side;
            vector <ofPoint> points = lines.at(j).getVertices();
            int k = 0;

            for (k = 0; k < points.size()-1; k++){
                ofPoint p1 = points.at(k+0);
                ofPoint p2 = points.at(k+1);

                side.addVertex(p1);
                side.addVertex(p2);
                side.addVertex(ofPoint(p1.x, p1.y, p1.z+extrusion_depth));
                side.addVertex(ofPoint(p2.x, p2.y, p2.z+extrusion_depth));
                side.addVertex(p2);
            }

            // connect the last to the first
            ofPoint p1 = points.at(k);
            ofPoint p2 = points.at(0);
            side.addVertex(p1);
            side.addVertex(p2);
            side.addVertex(ofPoint(p1.x, p1.y, p1.z+extrusion_depth));
            
            side.addVertex(ofPoint(p1.x, p1.y, p1.z+extrusion_depth));
            side.addVertex(ofPoint(p2.x, p2.y, p2.z+extrusion_depth));
            side.addVertex(p2);

            side.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

            all_meshes.push_back(side);
        }
    }

    return all_meshes;
}