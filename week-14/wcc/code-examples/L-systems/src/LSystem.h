#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Rule.h"
using namespace std;

class LSystem
{
    public:
        LSystem();
        void setup(string _axiom, vector<Rule> _ruleset);
        void generate();
        string getSentence();
        int getGeneration();

        string sentence;      // The sentence (a String)
        vector<Rule> ruleset; // The ruleset (an array of Rule objects)
        int generation;       // Keeping track of the generation #
};
