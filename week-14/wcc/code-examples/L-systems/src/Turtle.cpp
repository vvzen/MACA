#include "Turtle.h"

Turtle::Turtle(){

}
//==============================================
void Turtle::setup(string s, float l, float t){
    todo = s;
    len = l;
    theta = t;
}
//==============================================
void Turtle::render(){
    ofSetColor(0,175);
    for (int i = 0; i < todo.size(); i++) {
      char c = todo.at(i);
      if (c == 'F' || c == 'G') {
        ofDrawLine(0,0,len,0);
        ofTranslate(len,0);
      }
      else if (c == '+') {
        ofRotate(theta);
      }
      else if (c == '-') {
        ofRotate(-theta);
      }
      else if (c == '[') {
        ofPushMatrix();
      }
      else if (c == ']') {
        ofPopMatrix();
      }
    }
}
//==============================================
void Turtle::setLen(float _l){
    len = _l;
}
//==============================================
void Turtle::changeLen(float _percent){
    len *= _percent;
}
//==============================================
void Turtle::setToDo(string _s){
    todo = _s;
}
