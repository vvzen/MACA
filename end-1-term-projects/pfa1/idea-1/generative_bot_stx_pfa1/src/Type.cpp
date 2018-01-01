#include "ofApp.h"
#include "Type.h"

//--------------------------------------------------------------
vector<Word> generateTypography(ofxJSONElement jsonSource, ofTrueTypeFont & font, float verticalSize){

    string first_word = jsonSource[0]["word"].asString();
    vector <Word> words;

    int index = 0;
    int x_offset = font.getStringBoundingBox(first_word, 0, 0).getWidth();

    for (int y = 0; y < ofGetHeight(); y+=verticalSize){

        for (int x = 0; x < ofGetWidth(); x+=x_offset){

            int frequency = jsonSource[index]["score"].asInt();

            if (frequency > 4){

                Word current_word;
                // current_word.text = ofRandom(0, 2) == 1 ? "asd" : "asdfg";

                current_word.text = jsonSource[index]["word"].asString();
                // int index = x + y * (ofGetWidth() / word_bb.getWidth());
                ofRectangle word_bb = font.getStringBoundingBox(current_word.text, 0, 0);

                current_word.pos = ofVec2f(x, y);
                current_word.frequency = frequency;
                current_word.size = ofVec2f(word_bb.getWidth(), verticalSize);

                words.push_back(current_word);
                
                x_offset = word_bb.getWidth();

                cout << "word: " << current_word.text << ", offset: " << x_offset << endl;
                // verticalSize = word_bb.getHeight() * ofMap(frequency, 2, 315, 0.2, 1);
                
                // TODO: compute vertical offset
                // knowing that it must correspond to the vertical size
                //  of the letter in the row above
            }

            index++;
        }
    }
    return words;
}

//--------------------------------------------------------------
void renderTypography(ofFbo & fbo, vector<Word> words, ofTrueTypeFont & font){

    fbo.begin();

    ofPushStyle();
    ofClear(0);
    // ofBackground(0);
    // ofBackground(29, 17, 77);

    for (int i = 0; i < words.size(); i++){
        
        ofPushMatrix();
        float scale_factor = ofMap(words[i].frequency, 2, 315, 0.4, 1);

        ofTranslate(words[i].pos.x, words[i].pos.y);
        // ofScale(scale_factor, scale_factor, 1);
        
        // ofDrawRectangle(0, 0, words[i].size.x, words[i].size.y);
        
        ofPushMatrix();
        ofTranslate(0, words[i].size.y, 0);

        // ofColor color;
        // color.r = ofMap(i, 0, words.size(), 255, 0);
        // color.g = ofMap(i, 0, words.size(), 255, 0);
        // color.b = ofMap(i, 0, words.size(), 255, 0);

        ofSetColor(255);

        if (words[i].frequency % 2 == 0){
            font.drawString(words[i].text, 0, 0);
        }
        else {
            font.drawString(words[i].text, 0, 0);
            // font_demi_bold.drawStringAsShapes(words[i].text, 0, 0);
        }
        ofPopMatrix();
        
        // ofDrawRectangle(0, 0, words[i].size.x, words[i].size.y);

        // ofDrawCircle(0, 0, 5, 5);
        
        // if (scale_factor > 0.5){
        //     font_demi_bold.drawString(words[i].text, 0, words[i].pos.y);
        // }
        // else {
        //     font.drawString(words[i].text, 0, words[i].pos.y);
        // }

        ofPopMatrix();
    }

    // ofDisableBlendMode();
    ofPopStyle();

    fbo.end();
}