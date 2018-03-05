//This one isn't needed, just shows how to do similar type of sending as OF example sender in this directory
//Click the mouse somewhere to change x, y, colour

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress dest;

void setup() {
   size(400, 400);
   dest = new NetAddress("127.0.0.1",6448); //send messages to port 6448, localhost (this machine)
   oscP5 = new OscP5(this,12000); //listen for OSC messages on port 12000 (should NOT be same port!)

}

void draw() {
  background(0);
}


void mouseClicked() {
  OscMessage msg = new OscMessage("/processing/squarePosition");
  msg.add((float)mouseX);
  msg.add((float)mouseY);
  oscP5.send(msg, dest);
  
  msg = new OscMessage("/processing/changeColor");
  oscP5.send(msg, dest);
}

