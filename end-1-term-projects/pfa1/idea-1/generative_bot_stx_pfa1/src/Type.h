//
//  Type.h
//  generative_bot_stx_pfa1
//
//  Created by Valerio Viperino
//
//
#pragma once // include this file only once

#include "globals.h"
#include "ofMain.h"

// we don't need a full class, so we're
// just using a struct to host properties of each word
struct Word {
    ofVec2f pos;
    ofVec2f size;
	int frequency;
    string text;
};

// main function to generate the words positions 
vector<Word> generate_typography(ofxJSONElement jsonSource, ofTrueTypeFont & font, float verticalSize, bool vertical=false);
// draw the generative type on the given fbo
void render_typography(ofFbo & fbo, vector<Word> words, ofTrueTypeFont & font, bool vertical=false);