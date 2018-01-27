#include <CapacitiveSensor.h>

// PINS
#define LED_PIN 12

// the 4 is the sender, the 2 is the receiver
CapacitiveSensor sensor = CapacitiveSensor(4, 2);

int threshold = 1000;

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

}

void loop() {
  long sensor_value = sensor.capacitiveSensor(30); // how many samples we want to read
  Serial.print("sensor value: ");
  Serial.println(sensor_value);

  if (sensor_value > threshold){
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(10);
}
