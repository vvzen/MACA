/* piezoArray examples
 * Saskia Freeke / Term 1 / Week 3
 * 
 * Piezo on pin 9
 * connecting one of the piezo leg's to the pin and the other to the GND
 * more information on using array's see Arduino.cc
 */

/* making a array of 5 positions */
int freq[] = {1000,500,3300,1500,4000};

int playTime = 20;
int delayTime = 300;

void setup() { }

void loop() {

/* Example A  
 * between the brackets [ ] we are pointing to the position in the array we want to use
 * the first position starts at 0
 */
 
//    tone(9, freq[2], playTime);
//    delay(delayTime);



/* Example B  
 * Creating a for loop to loop through the position in the array
 */
    for (int i = 0; i < 5; i++){
      tone(9,freq[i],playTime);
      delay(delayTime);
    }
    
 
}
