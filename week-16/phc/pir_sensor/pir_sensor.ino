// Uses a PIR sensor to detect movement
 
const int LED_PIN = 13; // choose the pin for the LED
int PIR_PIN = 2; // choose the input pin (for PIR sensor)
int pir_state = LOW; // we start assuming no motion detected
int pir_value = 0; // current pin value
int calibration_time = 30; // seconds

void setup() {
  pinMode(LED_PIN, OUTPUT);    // declare LED as output
  pinMode(PIR_PIN, INPUT);     // declare sensor as input
  Serial.begin(9600);

  // give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibration_time; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

void loop(){
  
  pir_value = digitalRead(PIR_PIN);

  // check if the input is HIGH
  if (pir_value == HIGH) {
    digitalWrite(LED_PIN, HIGH); // turn LED ON
    
    if (pir_state == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pir_state = HIGH;
    }
  }
  else {
    digitalWrite(LED_PIN, LOW); // turn LED OFF
    delay(300);    
    if (pir_state == HIGH){
      // we have just turned off
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pir_state = LOW;
    }
  }
}
