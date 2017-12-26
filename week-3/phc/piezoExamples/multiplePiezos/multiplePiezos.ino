/* multiplePiezo examples
 * Saskia Freeke / Term 1 / Week 3
 * 
 * using 3 different piezo's on pin 7,8 & 9
 * connecting one of the piezo leg's to the pin and the other to the GND
 * more information on tone() function see Arduino.cc
 */

int pitch = 750;
int delayTime = 200;
int playTime = 20;

void setup() { }

void loop() {
  /*  Example A
   *  tone(pin number, frequency, time);
   *  adding a delay to stop in between each 
   */
   
//   tone(7, pitch, playTime);
//   delay(delayTime);

//   tone(8, pitch, playTime);
//   delay(delayTime);
//
//    tone(9, pitch, playTime);
//    delay(delayTime);

  /*  Example B: increase frequency
   *  still, use tone() + delay()
   *  adding 50 each time we run through the loop
   *  if pitch is above 4000, we go back to a pitch of 50
   *  leave tone() function above active
   */

//  pitch += 50;
//
//  if(pitch > 4000){
//    pitch = 50;
//  }

  /*  Example C: Small for loop but does the same
   *  When you have multiple things happening in the loop, 
   *  this might be a better option to use when you want to increase
   *  the frequency
   *  comment everythin above off 
   */

//    for (int i = 200; i < 4000; i+= 200){
//      tone(9,i,playTime);
//      delay(delayTime);
//    }


} // end of loop
