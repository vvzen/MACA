#include <Wire.h> // main library for I2C
#define SLAVE_ADDRESS 0x04

int number = 0; // received number
int state = 0; // current state of the led
String current_sentence = "";
int sentence_length = 0;
int current_byte_count = 0;
bool started_reception = false;

void setup() {
  pinMode(13, OUTPUT);

  Serial.begin(9600);

  // initialise i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receive_data);
  Wire.onRequest(send_data);

  Serial.println("Ready!");
}

void loop() {
  delay(100);
}


void receive_data(int byte_count){

  // the first byte tells how much the sentence is long
  if (current_byte_count == 0){
    int transmission_length = Wire.read();
    Serial.print("transmission length: ");
    Serial.println(transmission_length);
    started_reception = true;
    sentence_length = transmission_length;
  }
  // if we arrived at the end, stop
  else if (current_byte_count >= sentence_length){
      
      // reset byte count
      current_byte_count = 0;

      char current_char = Wire.read(); 
      current_sentence += current_char;
      
      //Serial.println("HERE!");
      Serial.println(current_sentence);
  }
  // in every other case, continue reading the message
  else {
    
    //current_sentence = "";
    
    while (Wire.available()){
      
      char current_char = Wire.read(); 
      current_sentence += current_char;
      
      Serial.print("current char: ");
      Serial.println(current_char);
      
      Serial.print("current byte count: ");
      Serial.println(current_byte_count);
    }
  }
  current_byte_count++;
}

void send_data(){
  Wire.write(current_sentence.c_str());
}

