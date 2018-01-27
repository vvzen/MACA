void setup() {
  Serial.begin(9600);
}

void loop() {
  // write to serial the r  eadings of our pot
  //Serial.println(analogRead(A0));
  int pot_value = analogRead(A0) / 4;
  Serial.println(pot_value);
  delay(1);
}
