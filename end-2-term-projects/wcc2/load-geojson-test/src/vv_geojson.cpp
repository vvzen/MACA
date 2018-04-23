#include "vv_geojson.h"

using namespace vv_map_projections;

//--------------------------------------------------------------
// @short:  loads the geojson map and fills the given vectors of ofVboMeshes.
// @desc:   currently supports the loading of Point, Polygon and MultiPolygon geojson feature types.
//          Creates the wireframe of the Polygon/Multipolygon features using a vector of ofVboMeshes,
//          and creates all the meshes for the name of each city (contained in ["features"][i]["properties"]["NAME_EN"] ).
//          Since I'm not going to change its geometry once created, I choose an ofVboMesh instead of a plain ofMesh.
// @args:   path: the path to the geojson file
//          font: the font used for the text extrusion
//          poly_meshes: a vector of ofVboMeshes that will be filled with polygonal contours
//          cities_meshes: a vector of city structs which host the meshes for the extruded cities names
//          scale: used to uniformly change the size of the mesh
// @return: the centroid of the mesh created from the geojson
//--------------------------------------------------------------
ofPoint vv_geojson::create_geojson_map(std::string path, ofTrueTypeFont & font, vector<ofVboMesh> & poly_meshes, vector<city> & cities_meshes, float scale){

    // std::string path = "world_cities_countries.geojson";
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
        // currently supported: Point, Polygon, MultiPolygon
        std::string type  = geojson_map["features"][i]["geometry"]["type"].asString();

        if (type == "Point"){
            float lon = coordinates[0].asFloat();
            float lat = coordinates[1].asFloat();

            std::string city_name = geojson_map["features"][i]["properties"]["NAME_EN"].asString();

            ofPoint projected = mercator(lon, lat, scale);

            // make lowercase and prepend hashtag to city name
            std::transform(city_name.begin(), city_name.end(), city_name.begin(), ::tolower);
            city_name = std::regex_replace(city_name, std::regex(","), "");
            city_name = "#" + city_name;

            // cout << "current city: " << city_name << endl;

            // excluding some cities for aesthetic reasons
            if (city_name != "#vatican city"){

                vector<ofVboMesh> city_name_meshes = extrude_mesh_from_text(city_name, font, 2, 0.012, true);
                
                city current_city;
                current_city.meshes = city_name_meshes;
                current_city.position = projected;
                current_city.name = city_name;
                cities_meshes.push_back(current_city);

            }
        }
        else if (type == "Polygon"){

            // we need to start a new ofVboMesh
            ofVboMesh mesh;

            int n_points = coordinates[0].size();

            //cout << "current i: " << i << ", type: " << type << ", n_points: " << n_points << endl;

            for (Json::ArrayIndex j = 0; j < n_points; ++j){
                
                float lon = coordinates[0][j][0].asFloat();
                float lat = coordinates[0][j][1].asFloat();

                //cout << "current point, float: "<< lon << ", " << lat << endl;

                ofPoint projected = mercator(lon, lat, scale);
                //cout << "current point after projection: "<< ofToString(projected) << endl;

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

            //cout << "current i: " << i << ", type: " << type << ", n_polygons: " << n_polygons << endl;
            
            for (Json::ArrayIndex k = 0; k < n_polygons; ++k){
                
                ofVboMesh mesh;

                int n_points = coordinates[k][0].size();

                for (Json::ArrayIndex j = 0; j < n_points; ++j){
                    float lon = coordinates[k][0][j][0].asFloat();
                    float lat = coordinates[k][0][j][1].asFloat();

                    ofPoint projected = mercator(lon, lat, scale);
                    //cout << "current point after projection: "<< ofToString(projected) << endl;
                    
                    mesh.addVertex(projected);
                    mesh.addColor(ofFloatColor(0.0));
                    mesh.addIndex(j);
                }
                mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
                // mesh.setMode(OF_PRIMITIVE_POINTS);
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