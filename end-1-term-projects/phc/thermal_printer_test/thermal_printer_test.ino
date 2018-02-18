/////////////////////////////////////////////
/////////////// DISPLAY STUFF ///////////////
/////////////////////////////////////////////
// BUSY (PURPLE) > PIN 7
// RST  (WHITE)  > PIN 9
// DC   (GREEN)  > PIN 8
// CS   (ORANGE) > PIN 10
// CLK  (YELLOW) > PIN 13
// DIN  (BLUE)   > PIN 11
// Supporting Arduino Forum Topics:
// Waveshare e-paper displays with SPI: http://forum.arduino.cc/index.php?topic=487007.0
// Good Dispay ePaper for Arduino : https://forum.arduino.cc/index.php?topic=436411.0

// include library, include base class, make path known
#include <GxEPD.h>

// select the display class to use
#include <GxGDEH029A1/GxGDEH029A1.cpp>      // 2.9" b/w

//#include GxEPD_BitmapExamples

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
//#include <Fonts/FreeMonoBold12pt7b.h>
//#include <Fonts/FreeMonoBold18pt7b.h>
//#include <Fonts/FreeMonoBold24pt7b.h>


#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

GxIO_Class io(SPI, SS, 8, 9); // arbitrary selection of 8, 9 selected for default of GxEPD_Class
GxEPD_Class display(io);

/////////////////////////////////////////////
/////////////// PRINTER STUFF ///////////////
/////////////////////////////////////////////
#include "Adafruit_Thermal.h"

// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"
#define TX_PIN 6 // DATA IN (BLUE)   labeled RX on printer
#define RX_PIN 5 // DATA OUT (GREEN) labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

/////////////////////////////////////////////
////////////////// MY STUFF /////////////////
/////////////////////////////////////////////
#define MARKOV_BUTTON 3 // button for printing markov chain stuff
//int timer = 0;
int serial_counter = 0;
char incoming_message[20] = "topolino";
bool message_received = false;

void setup(){
  
  Serial.begin(9600);
  Serial.println();
  Serial.println("setup");
  
  // DISPLAY
  display.init();

  // PRINTER
  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  //mySerial.begin(9600);  // Initialize SoftwareSerial
  
  printer.begin();        // Init printer (same regardless of serial type)
  printer.setDefault();

  // MY PINS
  //pinMode(MARKOV_BUTTON, INPUT);

  Serial.println("setup done!");
}

void loop(){

  delay(2000);
  //display.drawPaged(draw_serial_message);
  showFont(display, incoming_message, &FreeMonoBold9pt7b);
  
  if (message_received == true){
    
  }
  
  /*
  // when a serial message is received
  while (Serial.available() > 0){

    char current_char = Serial.read();

    if (current_char == '\n' && serial_counter > 0) {
      serial_counter = 0;
      //incoming_message[serial_counter] = '\0'; // add null value
      Serial.println("HERE");
      //Serial.println(incoming_message[0]);

      message_received = true;
    }
    else {
      //incoming_message[serial_counter] = current_char;
      serial_counter++;
      message_received = false;
    }
  }
  */

  /*
  if (digitalRead(MARKOV_BUTTON) == HIGH){
    Serial.println("mixed");
  }
  */
}

void showFont(GxEPD& display, const char name[], const GFXfont* f){

  //uint8_t rotation = display.getRotation();
  
  //display.setRotation(display_rot);
  
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.update();
  delay(5000);
  //display.setRotation(rotation); // restore
}
