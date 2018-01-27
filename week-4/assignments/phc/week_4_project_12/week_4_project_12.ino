#include <Servo.h>

// Pins
#define SWITCH_PIN 2
#define SERVO_PIN 9
#define PIEZO_PIN A0
#define RED_PIN 3
#define YELLOW_PIN 4
#define GREEN_PIN 5

int knock_value;
int switch_value;

const int quiet_knock = 40;
const int loud_knock = 200;

bool locked = false;
int num_of_knocks = 0;
const int required_num_locks = 3;

Servo servo;

void setup() {
  
  servo.attach(SERVO_PIN);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);

  Serial.begin(9600);

  servo.write(0);

  digitalWrite(GREEN_PIN, HIGH);
  Serial.println("The box is unlocked!");
}

void loop() {

  if (!locked){
    switch_value = digitalRead(SWITCH_PIN);
  }

  // when the button is pressed,
  // lock the mechanism
  if (switch_value == HIGH){
    locked = true;
    
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    
    servo.write(90);
    
    //Serial.println("The box is locked!");   

    delay(100);
  }

  if (locked){
    
    knock_value = analogRead(PIEZO_PIN);

    //Serial.print("knock value: ");
    //Serial.println(knock_value);

    if (num_of_knocks < required_num_locks && knock_value > 0){
      
      if (check_for_knock(knock_value) == true){
        num_of_knocks++;
      }
      Serial.print("\t");
      Serial.print(required_num_locks-num_of_knocks);
      Serial.println(" more knocks to go");
    }
    if (num_of_knocks >= required_num_locks){
      
      locked = false;

      num_of_knocks = 0;
      
      servo.write(0);
      delay(20);
    
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(RED_PIN, LOW);
      Serial.println("The box is unlocked!");  
    }
  }
}

bool check_for_knock(int value){

  if (value > quiet_knock && value < loud_knock){
    
    digitalWrite(YELLOW_PIN, HIGH);
    delay(50);
    digitalWrite(YELLOW_PIN, LOW);
    
    Serial.print("valid knock of value: ");
    Serial.println(value);

    return true;
  }
  else {
    Serial.print("Bad knock value: ");
    Serial.println(value);
    return false;
  }
}

