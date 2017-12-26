#define CALIBRATION_TIME 5000
// PINS
#define LIGHT_SENSOR A0
#define BUZZER 9
#define LED_PIN 13

int sensor_value;
int sensor_low = 1023;
int sensor_high = 0;

void setup() {

  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  // CALIBRATION
  while (millis() < CALIBRATION_TIME){
    sensor_value = analogRead(LIGHT_SENSOR);

    if (sensor_value > sensor_high){
      sensor_high = sensor_value;
    }
    if (sensor_value < sensor_low){
      sensor_low = sensor_value;
    }
  }
  digitalWrite(LED_PIN, LOW);

  /*
  tone(BUZZER, 50, 20);
  delay(1000);
  tone(BUZZER, 220, 20);
  delay(1000);
  tone(BUZZER, 440, 20);
  delay(1000);
  */
}

void loop() {

  sensor_value = analogRead(LIGHT_SENSOR);
  // hz
  int pitch = map(sensor_value, sensor_low, sensor_high, 50, 1200);

  // pin, frequency, length of note
  tone(BUZZER, pitch, 20);
  // give some time for the sound to play
  delay(10);
}
