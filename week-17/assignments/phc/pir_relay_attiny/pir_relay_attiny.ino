// Uses a PIR sensor to detect movement
 
const int LED_PIN = 0;
int PIR_PIN = 2; // PIR sensor
int RELAY_PIN = 1;
int pir_state = LOW; // we start assuming no motion detected
int pir_value = 0; // current pin value
int calibration_time = 30; // seconds

void setup() {
  pinMode(LED_PIN, OUTPUT);§
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  // give the sensor some time to calibrate
  // let led blink during calibration
  for(int i = 0; i < calibration_time; i++){
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
    digitalWrite(LED_PIN, HIGH);
  }
  delay(50);
}

void loop(){
  
  pir_value = digitalRead(PIR_PIN);

  // check if the input is HIGH
  if (pir_value == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(RELAY_PIN, HIGH);
    
    if (pir_state == LOW) {
      // we have just turned on
      pir_state = HIGH;
    }
  }
  else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
    delay(300);    
    if (pir_state == HIGH){
      // we have just turned off
      pir_state = LOW;
    }
  }
}
