// PINS
#define KEY_PIN A0
#define BASE_PIN 2
#define BUZZER_PIN 9
#define LED_PIN 13

//int notes[] = {262, 294, 330, 349}; // C, D, E, F in hz
int notes[] = {130, 155, 174, 196, 233}; // C, Eb, F, G, Eb in hz
int key_val;
int base_val;
int tolerance = 10;

void setup() {

  Serial.begin(9600);
  
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  key_val = analogRead(KEY_PIN);
  
  Serial.print("key val: ");
  Serial.println(key_val);
  
  if (key_val == 1023){
    tone(BUZZER_PIN, notes[0]);
  }
  else if (key_val > 1000 - tolerance && key_val < 1000 + tolerance){
    tone(BUZZER_PIN, notes[1], 20);
  }
  else if (key_val > 512 - tolerance && key_val < 512 + tolerance){
    tone(BUZZER_PIN, notes[2], 20);
  }
  else if (key_val > 970 - tolerance && key_val < 970 + tolerance){
    tone(BUZZER_PIN, notes[3], 20);
  }
  else {
    noTone(BUZZER_PIN);
    //tone(BUZZER_PIN, notes[0], 20);
    //digitalWrite(LED_PIN, LOW);
  }
}
