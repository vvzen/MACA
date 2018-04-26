#pragma once

#include "ofMain.h"

namespace vv_map_projections {
    
    ofPoint spherical_to_cartesian(float lon, float lat, float radius);
    ofPoint mercator(float lon, float lat, float scale);
}