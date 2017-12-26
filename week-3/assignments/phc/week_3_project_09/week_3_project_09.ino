// PINS
#define SWITCH_PIN 2
#define MOTOR_PIN 9

int switch_state = 0;

void setup() {
   pinMode(SWITCH_PIN, INPUT);
   pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  switch_state = digitalRead(SWITCH_PIN);

  if (switch_state == HIGH){
    digitalWrite(MOTOR_PIN, HIGH);
  }
  else {
    digitalWrite(MOTOR_PIN, LOW);
  }
}

