#include "vv_geojson.h"

using namespace vv_map_projections;

//--------------------------------------------------------------
// @short:  loads the geojson map and fills the given vectors of ofVboMeshes.
// @desc:   Creates the wireframe of the Polygon/Multipolygon features using a vector of ofVboMeshes.
//          Since I'm not going to change its geometry once created, I choose an ofVboMesh instead of a plain ofMesh.
// @args:   path: the path to the geojson file
//          poly_meshes: a vector of ofVboMesh-es that will be filled with the meshes of polygonal contours
//          scale: used to uniformly change the size of the mesh
// @return: the centroid of the mesh created from the geojson
//--------------------------------------------------------------
ofPoint vv_geojson::create_world_map(std::string path, vector<ofVboMesh> & poly_meshes, float scale){

    ofVboMesh poly_meshes_centroids;
    ofPoint geoshape_centroid = ofPoint(0, 0, 0);

    ofxJSONElement geojson_map;

    // Parse the JSON
    bool parsing_successful = geojson_map.open(path);

    if (parsing_successful){
        cout << "File " << path << " loaded correctly" << endl;
    }
    else {
        cout << "Failed to parse JSON" << endl;
    }

    cout << "number of total polygons: " << geojson_map["features"].size() << endl;

    // load each feature from the geojson
    for (Json::ArrayIndex i = 0; i < geojson_map["features"].size(); ++i){

        ofxJSONElement coordinates = geojson_map["features"][i]["geometry"]["coordinates"];
        
        // current geojson feature type
        std::string type  = geojson_map["features"][i]["geometry"]["type"].asString();

        if (type == "Polygon"){

            // we need to start a new ofVboMesh
            ofVboMesh mesh;

            int n_points = coordinates[0].size();

            for (Json::ArrayIndex j = 0; j < n_points; ++j){
                
                float lon = coordinates[0][j][0].asFloat();
                float lat = coordinates[0][j][1].asFloat();

                ofPoint projected = mercator(lon, lat, 1);
                projected *= scale;

                mesh.addVertex(projected);
                mesh.addColor(ofFloatColor(0.0));
            }

            mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
            poly_meshes.push_back(mesh);

            ofPoint mesh_centroid = mesh.getCentroid();

            poly_meshes_centroids.addVertex(mesh_centroid);
            poly_meshes_centroids.addColor(ofFloatColor(1.0, 0.0, 0.0));

            geoshape_centroid += mesh_centroid;
        }
        else if (type == "MultiPolygon"){
            
            int n_polygons = coordinates.size();

            for (Json::ArrayIndex k = 0; k < n_polygons; ++k){
                
                ofVboMesh mesh;

                int n_points = coordinates[k][0].size();

                for (Json::ArrayIndex j = 0; j < n_points; ++j){
                    float lon = coordinates[k][0][j][0].asFloat();
                    float lat = coordinates[k][0][j][1].asFloat();

                    ofPoint projected = mercator(lon, lat, 1);
                    projected *= scale;
                    
                    mesh.addVertex(projected);
                    mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));
                    mesh.addIndex(j);
                }

                mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
                
                poly_meshes.push_back(mesh);

                ofPoint mesh_centroid = mesh.getCentroid();

                poly_meshes_centroids.addVertex(mesh_centroid);
                poly_meshes_centroids.addColor(ofFloatColor(0.0, 0.0, 1.0));

                geoshape_centroid += mesh_centroid;
            }
        }
    }
    
    poly_meshes_centroids.setMode(OF_PRIMITIVE_POINTS);

    // set the overall geoshape centroid
    // making an average of the centroids
    geoshape_centroid /= poly_meshes_centroids.getNumVertices();
    
    return geoshape_centroid;
}