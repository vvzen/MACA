//Run this: Square position and colour controlled via OSC from OSF

import oscP5.*;
import netP5.*;

OscP5 oscP5;
float x = 100;
float y = 100;


void setup() {
   size(400, 400);
   oscP5 = new OscP5(this,6448);
   noStroke();
   
   int r = (int)random(0, 255);
   int g = (int)random(0, 255);
   int b = (int)random(0, 255);
   fill(r,g,b);

}

void draw() {
  background(0);
  rect(x, y, 100, 100);
  
}

void oscEvent(OscMessage theOscMessage) {
  /* get and print the address pattern and the typetag of the received OscMessage */
  println("### received an osc message with addrpattern "+theOscMessage.addrPattern()+" and typetag "+theOscMessage.typetag());
  theOscMessage.print();
  
   if (theOscMessage.checkAddrPattern("/processing/squarePosition") && theOscMessage.checkTypetag("ff")) {
        x = theOscMessage.get(0).floatValue(); //get first value in message
        y = theOscMessage.get(1).floatValue(); //get next value in message
   } else if (theOscMessage.checkAddrPattern("/processing/changeColor")) {
       int r = (int)random(0, 255);
       int g = (int)random(0, 255);
       int b = (int)random(0, 255);
       fill(r,g,b);
   } else {
        println("Error: unexpected params type tag received by Processing");
   }
}

