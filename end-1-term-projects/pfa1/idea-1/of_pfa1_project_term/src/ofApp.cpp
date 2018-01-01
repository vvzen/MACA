#include "ofApp.h"

//--------------------------------------------------------------
vector<Word> ofApp::generateTypography(ofxJSONElement jsonSource, ofTrueTypeFont & font, float verticalSize){

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
void ofApp::setup(){

    highest_count = 0;
    
    // TYPOGRAPHY
    // init fbo
    typography_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 8);

    vertical_size = 40;

    // fonts
    font.load("fonts/AvenirNext-Medium-06.ttf", vertical_size, true, true, true);
    font_demi_bold.load("fonts/Futura-Medium-01.ttf", vertical_size, true, true, true);
    // font.load("fonts/Futura-Medium-01.ttf", 32);

    std::string file_path = "words_frequency_score.json";

    // parse the json
    bool parsing_successful = JSON_words_count_score.open(file_path);

    if (!parsing_successful){
        ofLogNotice() << "Failed to parse input Json File!" << endl;
    }

    cout << "is JSON file array? "; 
    if (JSON_words_count_score.isArray()){
        cout << "yes" << endl;
    }
    else {
        cout << "not" << endl;
    }

    created_words = generateTypography(JSON_words_count_score, font, vertical_size);

    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
    renderTypography(typography_fbo, created_words);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    // ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    // ofSetColor(66, 23, 77);
    ofSetColor(255);
    ofSetLineWidth(2);
    ofNoFill();

    typography_fbo.draw(0, 0);

    // for (int i = 0; i < created_words.size(); i++){
        
    //     ofPushMatrix();
    //     float scale_factor = ofMap(created_words[i].frequency, 2, 315, 0.4, 1);

    //     ofTranslate(created_words[i].pos.x, created_words[i].pos.y);
    //     ofScale(scale_factor, scale_factor, 1);
        
    //     // ofDrawRectangle(0, 0, created_words[i].size.x, created_words[i].size.y);
        
    //     ofPushMatrix();
    //     ofTranslate(0, created_words[i].size.y, 0);

    //     ofColor color;
    //     color.r = ofMap(i, 0, created_words.size(), 255, 0);
    //     color.g = ofMap(i, 0, created_words.size(), 255, 0);
    //     color.b = ofMap(i, 0, created_words.size(), 255, 0);

    //     ofSetColor(color);

    //     if (created_words[i].frequency % 2 == 0){
    //         font.drawString(created_words[i].text, 0, 0);
    //     }
    //     else {
    //         font_demi_bold.drawString(created_words[i].text, 0, 0);
    //         // font_demi_bold.drawStringAsShapes(created_words[i].text, 0, 0);
    //     }
    //     ofPopMatrix();
        
    //     // ofDrawRectangle(0, 0, created_words[i].size.x, created_words[i].size.y);

    //     // ofDrawCircle(0, 0, 5, 5);
        
    //     // if (scale_factor > 0.5){
    //     //     font_demi_bold.drawString(created_words[i].text, 0, created_words[i].pos.y);
    //     // }
    //     // else {
    //     //     font.drawString(created_words[i].text, 0, created_words[i].pos.y);
    //     // }

    //     ofPopMatrix();
    // }

    // ofDisableBlendMode();
}

//--------------------------------------------------------------
void ofApp::renderTypography(ofFbo fbo, vector<Word> words){

    fbo.begin();

    ofClear(0);

    for (int i = 0; i < words.size(); i++){
        
        ofPushMatrix();
        float scale_factor = ofMap(words[i].frequency, 2, 315, 0.4, 1);

        ofTranslate(words[i].pos.x, words[i].pos.y);
        ofScale(scale_factor, scale_factor, 1);
        
        // ofDrawRectangle(0, 0, words[i].size.x, words[i].size.y);
        
        ofPushMatrix();
        ofTranslate(0, words[i].size.y, 0);

        ofColor color;
        color.r = ofMap(i, 0, words.size(), 255, 0);
        color.g = ofMap(i, 0, words.size(), 255, 0);
        color.b = ofMap(i, 0, words.size(), 255, 0);

        ofSetColor(color);

        if (words[i].frequency % 2 == 0){
            font.drawString(words[i].text, 0, 0);
        }
        else {
            font_demi_bold.drawString(words[i].text, 0, 0);
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

    fbo.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
