#include "vv_extrudeFont.h"

ofVboMesh extrude_mesh_from_text(string word, ofTrueTypeFont & font, float extrusion_depth){

    // contains all of the paths of the current word
    vector <ofPath> word_paths = font.getStringAsPoints(word, 0, 0);

    // meshes for the sides and the front of the 3d extruded text
    ofVboMesh text_mesh; // returned mesh (sides + front)

    // create the front mesh using a temporary ofPath and then extract its tessellation
    for (int i = 0; i < word_paths.size(); i++){

        // for every char break it into polyline
        // (simply a collection of the inner and outer points)
        vector <ofPolyline> char_polylines = word_paths.at(i).getOutline();

        ofVboMesh front; // the final vbos used to store the vertices
        ofPath front_path; // a temp path used for computing the tessellation of the letter shape

        // Now we build an ofPath using the vertices from the character polylines
        // First loop is for each polyline in the character
        // see http://openframeworks.cc/documentation/graphics/ofTrueTypeFont/#show_getStringAsPoints
        for (int c = 0; c < char_polylines.size(); c++){
            // Second loop is for each point on the polyline
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

        text_mesh.append(front);
        text_mesh.append(back);
    }

    // make the extruded sides
    for (int i = 0; i < word_paths.size(); i++){
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
            text_mesh.append(side);
        }
    }

    return text_mesh;
}