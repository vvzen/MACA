// Pins used
#define SWITCH_PIN 2
#define GREEN_LED 3
#define RED_LED_1 4
#define RED_LED_2 5

int switch_state;

void setup() {
  pinMode(SWITCH_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED_1, OUTPUT);
  pinMode(RED_LED_2, OUTPUT);
}

void loop() {
  switch_state = digitalRead(SWITCH_PIN);

  if (switch_state == LOW){
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED_1, LOW);
    digitalWrite(RED_LED_2, LOW);
  }
  else {
    digitalWrite(GREEN_LED, LOW);
    // make the red leds blink
    digitalWrite(RED_LED_1, LOW);
    digitalWrite(RED_LED_2, HIGH);
    // wait
    delay(250);
    digitalWrite(RED_LED_1, HIGH);
    digitalWrite(RED_LED_2, LOW);
    delay(250);
  }
}
