void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  int pot_value = get_pot_value();
  Serial.print("pot_value: ");
  Serial.println(pot_value);
}


int get_pot_value(){
  
  int pot_value = analogRead(A0);
  Serial.print("sensor_value: ");
  Serial.println(pot_value);

  if (pot_value >= 1000){
    return 0;
  }
  else if(pot_value >= 965 && pot_value < 1000){
    return 1;
  }
  else if(pot_value >= 494 && pot_value < 965){
    return 2;
  }
  else {
    return 3;
  }
}

