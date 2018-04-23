#include "vv_extrude_font.h"


//--------------------------------------------------------------
// Original credits go to jefftimeisten, see https://forum.openframeworks.cc/t/extrude-text-into-3d/6938
//
// This method returns a vector containing the vbo meshes required
// to render the front, back and sides of each character in the given string.
// ALERT! Spaces inside the passed string will be converted to underscores.
//
// @example:
//
// void ofApp::setup(){
       // my_extruded_word is a vector<ofVboMesh>
//     my_extruded_word = extrude_mesh_from_text(word, font, extrusion_depth, scale);
// }
// 
// void ofApp::draw(){
//     ofPushMatrix();
//     ofScale(1, -1, 1); // flip y axis
//     for (int m = 0; m < my_extruded_word.size(); m++){
//         my_extruded_word.at(m).draw();
//     }
//     ofPopMatrix();
// }
//--------------------------------------------------------------
vector<ofVboMesh> extrude_mesh_from_text(string word, ofTrueTypeFont & font, float extrusion_depth, float scale=1, bool get_front_only=false){

    // replace spaces with underscores
    std::replace(word.begin(), word.end(), ' ', '_');

    // contains all of the paths of the current word
    // last argument is the numer of samples
    vector <ofPath> word_paths = get_string_as_sampled_points(font, word, 60);

    vector <ofVboMesh> front_meshes, back_meshes, side_meshes;

    // meshes for the sides and the front of the 3d extruded text
    vector<ofVboMesh> all_meshes; // returned meshese (sides + front + back)

    // for every character, get its path
    for (int i = 0; i < word_paths.size(); i++){

        ofVboMesh current_char_mesh;
        
        // 1. create the front mesh using a temporary ofPath and then extract its tessellation

        // for every character break it out to polylines
        // (simply a collection of the inner and outer points)
        vector <ofPolyline> char_polylines = word_paths.at(i).getOutline();

        ofVboMesh front; // the final vbos used to store the vertices
        ofPath front_path; // a temp path used for computing the tessellation of the letter shape

        // now we build an ofPath using the vertices from the character polylines
        // first loop is for each polyline in the character
        for (int c = 0; c < char_polylines.size(); c++){

            // FRONT AND BACK
            // this loop is for each point on the polyline
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

        // compute the front by just offsetting the vertices of the required amount
        ofVboMesh back = front_path.getTessellation();
        ofVec3f * back_vertices = back.getVerticesPointer();

        for (int v = 0; v < front.getNumVertices(); v++){
            front_vertices[v].z += extrusion_depth;
            // scale the mesh
            front_vertices[v] *= scale;
            back_vertices[v] *= scale;
        }

        current_char_mesh.append(front);
        if (!get_front_only) current_char_mesh.append(back);

        all_meshes.push_back(current_char_mesh);

        if (!get_front_only) {

            // 2. make the extruded sides
            vector <ofPolyline> lines = word_paths.at(i).getOutline();
            for (int j = 0; j < char_polylines.size(); j++){

                // SIDES
                ofVboMesh side;
                vector <ofPoint> points = char_polylines.at(j).getVertices();
                // vector <ofPoint> points = char_polylines[c];
                int k = 0;

                for (k = 0; k < points.size()-1; k++){
                    
                    // skip half of the points
                    ofPoint p1 = points.at(k+0);
                    ofPoint p2 = points.at(k+1);
                    
                    // // scale the mesh
                    p1 *= scale;
                    p2 *= scale;

                    side.addVertex(p1);
                    side.addVertex(p2);
                    side.addVertex(ofPoint(p1.x, p1.y, p1.z + extrusion_depth * scale));
                    side.addVertex(ofPoint(p2.x, p2.y, p2.z + extrusion_depth * scale));
                    side.addVertex(p2);
                }

                // connect the last to the first
                ofPoint p1 = points.at(k);
                ofPoint p2 = points.at(0);

                // scale the mesh
                p1 *= scale;
                p2 *= scale;

                side.addVertex(p1);
                side.addVertex(p2);
                side.addVertex(ofPoint(p1.x, p1.y, p1.z + extrusion_depth * scale));
                
                side.addVertex(ofPoint(p1.x, p1.y, p1.z + extrusion_depth * scale));
                side.addVertex(ofPoint(p2.x, p2.y, p2.z + extrusion_depth * scale));
                side.addVertex(p2);

                side.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

                all_meshes.push_back(side);
            }
        }
    }

    return all_meshes;
}

//--------------------------------------------------------------
// this handy method can be used as a substitute of the default font.getStringAsPoints()
// since it gives you the chance to resample the polylines and get a lower number of points (thus optimising speed)
//--------------------------------------------------------------
vector <ofPath> get_string_as_sampled_points(ofTrueTypeFont & font, string s, int num_of_samples){

    vector <ofPath> string_paths;
    vector <ofTTFCharacter> paths = font.getStringAsPoints(s);

    // find the biggest character in terms of perimeter (used for uniform resampling)
    int max_perimeter = 0;
    for (int i = 0; i < paths.size(); i++){
       vector <ofPolyline> polylines = paths[i].getOutline();
       for (int j = 0; j < polylines.size(); j++){
           if (polylines[j].getPerimeter() > max_perimeter) max_perimeter = polylines[j].getPerimeter();
       }
    }
    // for every character, get its path
    for (int i = 0; i < paths.size(); i++){
        // for every character break it out to polylines
        vector <ofPolyline> polylines = paths[i].getOutline();

        // this path will store the new points sampled
        ofPath current_path;

        // for every polyline, resample it
        for (int j = 0; j < polylines.size(); j++){

            // int num_of_points = ofMap(polylines[j].getPerimeter(), 0, max_perimeter, 0, num_of_samples, true);
            int num_of_points = num_of_samples;

            for (int i = 0; i < num_of_points; i++){
                if (i == 0){
                    current_path.moveTo(ofPoint(polylines[j].getPointAtPercent(float(i+1) / num_of_points)));
                }
                else {
                    current_path.lineTo(ofPoint(polylines[j].getPointAtPercent(float(i+1) / num_of_points)));
                }
            }
            current_path.close();
        }
        string_paths.push_back(current_path);
    }

    return string_paths;
}