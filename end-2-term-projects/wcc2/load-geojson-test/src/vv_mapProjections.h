#pragma once

#include "ofMain.h"

namespace vvMapProjections {
    
    ofPoint spherical_to_cartesian(float lon, float lat, float radius);
    ofPoint mercator(float lon, float lat, float scale);
}