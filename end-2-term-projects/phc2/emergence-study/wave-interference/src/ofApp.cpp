#include "ofApp.h"

#define USE_TRIANGLE_STRIPS 1

//--------------------------------------------------------------
void ofApp::setup(){

    light.setPosition(ofPoint(0, 0, 50));
    light.setPointLight();
    cam.setDistance(80);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);

    cam.begin();
    
    ofDrawAxis(100);
    
    light.enable();

    ofPushMatrix();
    ofTranslate(-WIDTH/2, -HEIGHT/2);

    ofSetColor(255, 0, 0);
    // visualize the random "dropped" points
    for (int i = 0; i < random_points.size(); i++){
        ofDrawSphere(random_points.at(i).x, random_points.at(i).y, 2, 2);
    }

    ofSetColor(255);
    mesh.draw();  
    // mesh.drawWireframe();

    ofPopMatrix();

    light.disable();
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::generate_mesh_2(ofVboMesh &mesh){

    vector<ofPoint> points;
    
    int cols = 8;  
	int rows = 8;  

    // Mesh indices  
    int totalQuads		= (cols-1) * (rows-1);  
    int totalTriangles	= totalQuads * 2;  
    int totalIndices	= (cols*2) * (rows-1);  
    cout << "total number of quads: " << totalQuads << endl;  
    cout << "total number of triangles: " << totalTriangles << endl;  
    cout << "total number of indices: " << totalIndices << endl;  
        
    bool isGoingBackwards = false;  
    int n	= 0;  
    int colSteps = cols * 2;  
    int rowSteps = rows - 1;  
    vector<int> indices;  
    for ( int r = 0; r < rowSteps; r++ ) {  
        for ( int c = 0; c < colSteps; c++ ) {  
            int t = c + r * colSteps;  
            
            if ( c == colSteps - 1 ) {  
                indices.push_back( n );  
            }  
            else {  
                indices.push_back( n );  
            
                ( t%2 == 0 ) ? n += cols : (r%2 == 0) ? n -= (cols-1) : n -= (cols+1);  
            }  
        }  
    }

    for (int a = 0; a < indices.size(); a++){  
        mesh.addIndex( indices[a] );  
    }

    int spaceX = 100;  
	int spaceY = 100;  

    // Points positions  
    for (int y = 0; y < rows; y++){  
        for ( int x = 0; x < cols; x++){  
            ofVec2f point( x * spaceX, y * spaceY );  
            points.push_back( point );  
            mesh.addVertex( point );  
        }  
    }

    int num_random_points = 4;
    float max_distance = 0;
    float frequency = 4;
    float overall_multiplier = 2;

    cout << "generating random points" << endl;
    // 2.1 find the max distance between the vertices
    // and some random chosen points on the grid
    // TODO: optimize using sort()
    for (int i = 0; i < num_random_points; i++){
        
        ofPoint random_point = ofPoint(ofRandom(WIDTH), ofRandom(HEIGHT));
        random_points.push_back(random_point);

        for (int p = 0; p < mesh.getNumVertices(); p++){

            ofPoint mesh_point = ofPoint(mesh.getVertex(p));

            float current_distance = ofDist(random_point.x, random_point.y, mesh_point.x, mesh_point.y);
            if (current_distance > max_distance){
                max_distance = current_distance;
            }
        }
    }

    cout << "applying amplitude" << endl;
    // 2.2 apply the amplitude to the y axis of the vertex
    for (int r = 0; r < random_points.size(); r++){
        
        ofPoint random_point = random_points.at(r);

        for (int i = 0; i < mesh.getNumVertices(); i++){

            ofPoint mesh_point = mesh.getVertex(i);
            
            float current_distance = ofDist(random_point.x, random_point.y, mesh_point.x, mesh_point.y);
            // amp gets weaker the more distant it is from the point
            float amp_strength = ofMap(current_distance, 0, max_distance, 0.5, 0);
            float current_amplitude = sin(current_distance * frequency) * amp_strength * overall_multiplier;
            mesh_point.z += current_amplitude;
            
            mesh.setVertex(i, mesh_point);
        }
    }

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}

//--------------------------------------------------------------
void ofApp::generate_mesh(ofVboMesh &mesh){

    mesh.clear();

    // 1. generate a grid with a triangle strip
    for (int x = 0; x < WIDTH; x++){
        for (int y = 0; y < HEIGHT; y++){
            mesh.addVertex(ofPoint(x, y));
            mesh.addColor(ofFloatColor(0.5));
        }
    }

    for (int y = 0; y < HEIGHT-1; y++){
        for (int x = 0; x < WIDTH-1; x++){
            mesh.addIndex(x+y*WIDTH);         // 0
            mesh.addIndex((x+1)+y*WIDTH);     // 1
            mesh.addIndex(x+(y+1)*WIDTH);     // 10

            mesh.addIndex((x+1)+y*WIDTH);     // 1
            mesh.addIndex((x+1)+(y+1)*WIDTH); // 11
            mesh.addIndex(x+(y+1)*WIDTH);     // 10
        }
    }

    int num_random_points = 4;
    float max_distance = 0;
    float frequency = 4;
    float overall_multiplier = 2;

    cout << "generating random points" << endl;
    // 2.1 find the max distance between the vertices
    // and some random chosen points on the grid
    // TODO: optimize using sort()
    for (int i = 0; i < num_random_points; i++){
        
        ofPoint random_point = ofPoint(ofRandom(WIDTH), ofRandom(HEIGHT));
        random_points.push_back(random_point);

        for (int p = 0; p < mesh.getNumVertices(); p++){

            ofPoint mesh_point = ofPoint(mesh.getVertex(p));

            float current_distance = ofDist(random_point.x, random_point.y, mesh_point.x, mesh_point.y);
            if (current_distance > max_distance){
                max_distance = current_distance;
            }
        }
    }

    cout << "applying amplitude" << endl;
    // 2.2 apply the amplitude to the y axis of the vertex
    for (int r = 0; r < random_points.size(); r++){
        
        ofPoint random_point = random_points.at(r);

        for (int i = 0; i < mesh.getNumVertices(); i++){

            ofPoint mesh_point = mesh.getVertex(i);
            
            float current_distance = ofDist(random_point.x, random_point.y, mesh_point.x, mesh_point.y);
            // amp gets weaker the more distant it is from the point
            float amp_strength = ofMap(current_distance, 0, max_distance, 0.5, 0);
            float current_amplitude = sin(current_distance * frequency) * amp_strength * overall_multiplier;
            mesh_point.z += current_amplitude;
            
            mesh.setVertex(i, mesh_point);
        }
    }

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

}
//--------------------------------------------------------------
ofVec3f ofApp::getNormalFromTriangleVertices(vector<ofVec3f> triangleVertices){

    // now is same as RedBook (OpenGL Programming Guide)  
    ofVec3f u = triangleVertices[0] - triangleVertices[1];  
    ofVec3f v = triangleVertices[1] - triangleVertices[2];  
	  
	/*cout << " triangleVertices[0].x: " << triangleVertices[0].x << " triangleVertices[0].y: " << triangleVertices[0].y << " triangleVertices[0].z: " << triangleVertices[0].z << endl;  
	cout << " triangleVertices[1].x: " << triangleVertices[1].x << " triangleVertices[1].y: " << triangleVertices[1].y << " triangleVertices[1].z: " << triangleVertices[1].z << endl;  
	cout << " triangleVertices[2].x: " << triangleVertices[2].x << " triangleVertices[2].y: " << triangleVertices[2].y << " triangleVertices[2].z: " << triangleVertices[2].z << endl;  
	  
	  
	cout << " u.x: " << u.x << " u.y: " << u.y << " u.z: " << u.z << endl;  
	cout << " v.x: " << v.x << " v.y: " << v.y << " v.z: " << v.z << endl;*/  
	  
	ofVec3f normal = u.getPerpendicular(v);  
	//cout << " normal.x: " << normal.x << " normal.y: " << normal.y << " normal.z: " << normal.z << endl;  
    return normal;  
}  


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'g'){
        generate_mesh_2(mesh);
    }
    if (key == 's'){
        mesh.save("interference.ply");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
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
