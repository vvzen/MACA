#include <Wire.h> // main library for I2C
#define SLAVE_ADDRESS 0x04

int number = 0; // received number
int state = 0; // current state of the led

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

  while (Wire.available()){
    number = Wire.read();
    Serial.print("data received: ");
    Serial.println(number);

    if (number == 1){
      switch (state){
        case 0:{
          digitalWrite(13, HIGH);
          state == 1;
          break;
        }
        case 1:{
          digitalWrite(13, LOW);
          state == 0;
          break;
        }
      }
    }
  }
}

void send_data(){
  Wire.write(number);
}

