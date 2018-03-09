#include <Wire.h> // main library for I2C
#include <Servo.h>

#define SLAVE_ADDRESS 0x04
#define SERVO_PIN 9

Servo servo;
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

  servo.attach(SERVO_PIN);

  Serial.println("Ready!");

  servo.write(0);
}

void loop() {
  
  delay(100);
}


void receive_data(int byte_count){

  while (Wire.available()){
    number = Wire.read();
    Serial.print("data received: ");
    Serial.println(number);

    switch (number){
        case 1:{
          servo.write(10);
          delay(15);
          break;
        }
        case 2:{
          servo.write(20);
          delay(15);
          break;
        }
        case 3:{
          servo.write(30);
          delay(15);
          break;
        }
        case 4:{
          servo.write(40);
          delay(15);
          break;
        }
    }
  }
}

void send_data(){
  Wire.write(number);
}

