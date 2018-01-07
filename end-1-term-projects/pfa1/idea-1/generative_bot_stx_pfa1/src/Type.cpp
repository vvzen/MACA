#include "ofApp.h"
#include "Type.h"

//--------------------------------------------------------------
vector<Word> generate_typography(ofxJSONElement jsonSource, ofTrueTypeFont & font, float verticalSize, bool vertical){

    vector <Word> words;

    int index = 0;
    // use the first word to compute the first horizontal offset (where should the second word appear)
    string first_word = jsonSource[index]["word"].asString();
    int x_offset = font.getStringBoundingBox(first_word, 0, 0).getWidth();

    int outer_limit;
    int inner_limit;

    // if requested, put the artwork in portrait mode
    if (vertical){
        outer_limit = OUTPUT_WIDTH;
        inner_limit = OUTPUT_HEIGHT;
    }
    else {
        outer_limit = OUTPUT_HEIGHT;
        inner_limit = OUTPUT_WIDTH;
    }
    // this loops only works when there are a lot of words,
    // since we know that 'index' will be less than the number of words

    // add all the words to the returned vector
    for (int y = 0; y < outer_limit; y+=verticalSize){
        for (int x = 0; x < inner_limit; x+=x_offset){

            int appeareances = jsonSource[index]["score"].asInt();

            // pick only most frequent words
            if (appeareances > 2){

                Word current_word;

                current_word.text = jsonSource[index]["word"].asString();
                ofRectangle word_bb = font.getStringBoundingBox(current_word.text, 0, 0);

                current_word.pos = ofVec2f(x, y);
                current_word.frequency = appeareances;
                current_word.size = ofVec2f(word_bb.getWidth(), verticalSize);

                words.push_back(current_word);
                
                x_offset = word_bb.getWidth();
            }

            index++;
        }
    }
    return words;
}

//--------------------------------------------------------------
void render_typography(ofFbo & fbo, vector<Word> words, ofTrueTypeFont & font, bool vertical){

    fbo.begin();

    ofPushStyle();
    ofClear(0);
    ofSetColor(255);
    // if requested, put the artwork in portrait mode
    if (vertical){
        ofTranslate(fbo.getWidth()/2, fbo.getHeight()/2);
        ofRotateZ(90);
        ofTranslate(-fbo.getHeight()/2, -fbo.getWidth()/2, 0);
    }

    // render all the words in the vector
    for (int i = 0; i < words.size(); i++){
        
        ofPushMatrix();

        ofTranslate(words[i].pos.x, words[i].pos.y);
        float scale_factor = ofRandom(0.4, 1);
        ofScale(scale_factor, scale_factor, 1);
        
        // use the draw rectangle to debug the position of the words
        // ofDrawRectangle(0, 0, words[i].size.x, words[i].size.y);
        
        ofPushMatrix();
        ofTranslate(0, words[i].size.y, 0);

        // throw a dice, with 1 we hide contours of the current word
        if (int(ofRandom(6)) == 1){
            ofNoFill();
            font.drawStringAsShapes(words[i].text, 0, 0);
        }
        else {
            ofFill();
            font.drawString(words[i].text, 0, 0);
        }

        ofPopMatrix();

        ofPopMatrix();
    }

    ofPopStyle();

    fbo.end();
}