#pragma once
#include "ofMain.h"

class Turtle
{
    public:
        Turtle();
        void setup(string s, float l, float t);
        void render();
        void setLen(float _l);
        void changeLen(float _percent);
        void setToDo(string _s);

        string todo;
        float len;
        float theta;
};
