//
//  Type.h
//  generative_bot_stx_pfa1
//
//  Created by Valerio Viperino on 31/12/17.
//
//

#include "ofMain.h"

// main function to generate the words positions 
vector<Word> generateTypography(ofxJSONElement jsonSource, ofTrueTypeFont & font, float verticalSize);
// draw the generative type on the given fbo
void renderTypography(ofFbo & fbo, vector<Word> words, ofTrueTypeFont & font);