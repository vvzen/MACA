#include "LSystem.h"

LSystem::LSystem(){
}
//===============================================================================
void LSystem::setup(string _axiom, vector<Rule> _ruleset){
    sentence = _axiom;
    ruleset = _ruleset;
    generation = 0;
}
//===============================================================================
// Generate the next generation
void LSystem::generate() {
    // An empty string that we will fill
    string nextgen;
    // For every character in the sentence
    for (int i = 0; i < sentence.length(); i++) {
        // What is the character
        char curr = sentence.at(i);
        // We will replace it with itself unless it matches one of our rules
        string replace = string(1, curr);
        // Check every rule
        for (int j = 0; j < ruleset.size(); j++) {
            char a = ruleset[j].getA();
            // if we match the Rule, get the replacement String out of the Rule
            if (a == curr) {
                replace = ruleset[j].getB();
                break;
            }
        }
        nextgen+=replace;
    }
    // Replace sentence
    sentence = nextgen;
    // Increment generation
    generation++;
}
//===============================================================================
string LSystem::getSentence() {
    return sentence;
}
//===============================================================================
int LSystem::getGeneration() {
    return generation;
}
