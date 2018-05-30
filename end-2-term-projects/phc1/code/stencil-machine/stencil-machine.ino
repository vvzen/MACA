// Name: Valerio Viperino
// Course: Physical Computing
// Assignment: Term 1 Final Project

// Project Title: SASM - Super Artsy Stencil Machine
// "Make an physical computing project that perhaps solves some sort of problem"

#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// SERVOS
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // connect to analog pin 4 and 5 (used for I2C)

#define SERVOUP   420 // pwm frequency
#define SERVODOWN 560

uint8_t total_servos = 1;

// STEPPER
const int FWD_PIN = 2;
const int BCK_PIN = 3;

uint8_t steps_movement = 200;
uint8_t distance = 0;

// initialize the stepper library on pins 8 through 11
Stepper stepper(steps_movement, 8, 9, 10, 11);

void setup() {

  // initialize the serial port:
  Serial.begin(9600);

  // STEPPER
  stepper.setSpeed(240); // rpm

  // buttons
  pinMode(FWD_PIN, INPUT);
  pinMode(BCK_PIN, INPUT);

  // SERVOS
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates

  // raise the servos
  pwm.setPWM(0, 0, SERVOUP);
  pwm.setPWM(1, 0, SERVOUP);

  delay(10);
}

void loop() {

  // read servo position from the trimpot
  int servo_rotation = map(analogRead(A0), 0, 1023, SERVOUP, SERVODOWN);

  pwm.setPWM(0, 0, servo_rotation);
  pwm.setPWM(1, 0, servo_rotation);
  
  delay(100);
  
  if (digitalRead(FWD_PIN) == HIGH){
    // move the stepper
    advance(true);
  }
  if (digitalRead(BCK_PIN) == HIGH){
    advance(false);
  }
}

// ADVANCE ON THE RAILS
void advance(bool forward){

  if (forward){
    // step one revolution  in one direction:
    Serial.println("clockwise");
    stepper.step(steps_movement);
    delay(100);
    distance++;
  }
  else {
    // step one revolution in the other direction:
    Serial.println("counterclockwise");
    stepper.step(-steps_movement);
    delay(100);  
    distance--;
  }
  
  Serial.print("distance: ");
  Serial.println(distance);
}

