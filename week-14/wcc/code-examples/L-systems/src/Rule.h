#pragma once
#include <string>
using namespace std;

class Rule
{
    public:
        Rule(char _a, string _b);
        char getA();
        string getB();

        char a;
        string b;
};
