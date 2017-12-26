#include <Servo.h>

// PINS
#define POT A0
#define SERVO_PIN 9

Servo servo;

int pot_value;
int angle;

void setup() {

  servo.attach(SERVO_PIN);

  Serial.begin(9600);
}

void loop() {
  // read the potentiometer
  pot_value = analogRead(POT);
  angle = map(pot_value, 1023, 0, 0, 179);
  // move the servo
  servo.write(angle);
  delay(15);
}
