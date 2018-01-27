// a variation of the spaceship interface
// using a 4 way 4 pole switch

const int GREEN_LED = 8;
const int RED_LED_1 = 9;
const int RED_LED_2 = 10;
int pot_states[4];

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED_1, OUTPUT);
  pinMode(RED_LED_2, OUTPUT);
  // setup the 4 pins for the switch
  for (int i = 2; i < 6; i++){
    pinMode(i, INPUT_PULLUP);
  }
}
void loop() {
  for (int i = 0; i < 4; i++){
    pot_states[i] = digitalRead(i+2);
  }
  
  if (pot_states[0] == LOW){
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED_1, LOW);
    digitalWrite(RED_LED_2, LOW);
  }
  else if (pot_states[1] == LOW){
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED_1, HIGH);
    digitalWrite(RED_LED_2, LOW);
  }
  else if (pot_states[2] == LOW){
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED_1, LOW);
    digitalWrite(RED_LED_2, HIGH);
  }
  else if (pot_states[3] == LOW){
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED_1, LOW);
    digitalWrite(RED_LED_2, LOW);
  }
}
