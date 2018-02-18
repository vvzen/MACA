

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {

  digitalWrite(13, LOW);
  
  if (Serial.available() > 0){
    String received_message = Serial.readString();
    Serial.println(received_message);
  }

  delay(15);

}
