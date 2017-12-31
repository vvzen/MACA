#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    highest_count = 0;
    
    // fonts
    font.load("fonts/AvenirNext-Medium-06.ttf", 12);
    font_demi_bold.load("fonts/AvenirNextCondensed-DemiBold-03.ttf", 110);
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

    // for (Json::ArrayIndex i = 0; i < JSON_words_count_score.size(); ++i){

    //     cout << JSON_words_count_score[i]["word"].asString() << " : " << JSON_words_count_score[i]["score"].asInt() << endl;

    //     int frequency = JSON_words_count_score[i]["score"].asInt();

    //     if (frequency > 1){
    //         // fill our map with the json keys and values
    //         words_count_score[JSON_words_count_score[i]["word"].asString()] = frequency;

    //         // pick a random location
    //         Word current_word;
    //         current_word.text = JSON_words_count_score[i]["word"].asString();
    //         ofRectangle word_bb = font.getStringBoundingBox(current_word.text, 0, 0);
    //         float x = ofRandom(word_bb.getWidth()/2 , ofGetWidth() - word_bb.getWidth()/2 );
    //         float y = ofRandom(word_bb.getHeight()/2 , ofGetHeight() - word_bb.getHeight()/2);        

    //         current_word.pos = ofVec2f(x, y);
    //         current_word.frequency = frequency;
    //         current_word.size = ofVec2f(word_bb.getWidth(), word_bb.getHeight());

    //         created_words.push_back(current_word);
    //     }

    // }

    string first_word = JSON_words_count_score[0]["word"].asString();

    int index = 0;
    int x_offset = font.getStringBoundingBox(first_word, 0, 0).getWidth();

    for (int y = 0; y < ofGetHeight(); y+=12){

        for (int x = 0; x < ofGetWidth(); x+=x_offset){

            string next_word = JSON_words_count_score[index+1]["word"].asString();

            Word current_word;
            // current_word.text = ofRandom(0, 2) == 1 ? "asd" : "asdfg";

            current_word.text = JSON_words_count_score[index]["word"].asString();
            // int index = x + y * (ofGetWidth() / word_bb.getWidth());
            ofRectangle word_bb = font.getStringBoundingBox(current_word.text, 0, 0);
            ofRectangle next_word_bb = font.getStringBoundingBox(next_word, 0, 0);

            current_word.pos = ofVec2f(x, y);
            current_word.frequency = 1;
            current_word.size = ofVec2f(word_bb.getWidth(), 12);

            created_words.push_back(current_word);

            x_offset = word_bb.getWidth();
            index++;
        }
    }

    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    // ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    ofSetColor(66, 23, 77);
    ofNoFill();

    for (int i = 0; i < created_words.size(); i++){
        
        ofPushMatrix();
        float scale_factor = ofMap(created_words[i].frequency, 2, 315, 0.07, 1);

        ofTranslate(created_words[i].pos.x, created_words[i].pos.y);
        // ofScale(scale_factor, scale_factor, 1);
        
        ofSetColor(255, 0, 0);
        font.drawString(created_words[i].text, 0, created_words[i].size.y);
        // ofDrawRectangle(0, 0, created_words[i].size.x, created_words[i].size.y);
        
        ofSetColor(0);
        // ofDrawRectangle(0, 0, created_words[i].size.x, created_words[i].size.y);

        // ofDrawCircle(0, 0, 5, 5);
        
        // if (scale_factor > 0.5){
        //     font_demi_bold.drawString(created_words[i].text, created_words[i].pos.x, created_words[i].pos.y);
        // }
        // else {
        //     font.drawString(created_words[i].text, created_words[i].pos.x, created_words[i].pos.y);
        // }

        ofPopMatrix();
    }

    // ofDisableBlendMode();
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
