// PINS
#define CONTROL_PIN_1 2
#define CONTROL_PIN_2 3
#define MOTOR_ENABLE_PIN 9
#define DIRECTION_CHANGE_PIN 4
#define ON_OFF_SWITCH_PIN 5
#define POT_PIN A0

int on_off_switch_state = 0;
int previous_on_off_switch_state = 0;
int direction_switch_state = 0;
int previous_direction_switch_state = 0;

int motor_enabled = 0;
int motor_speed = 0;
int motor_direction = 1;

void setup() {

  Serial.begin(9600);
  
  pinMode(DIRECTION_CHANGE_PIN, INPUT);
  pinMode(ON_OFF_SWITCH_PIN, INPUT);
   
  pinMode(CONTROL_PIN_1, OUTPUT);
  pinMode(CONTROL_PIN_2, OUTPUT);
  pinMode(MOTOR_ENABLE_PIN, OUTPUT);

  // turn off motor
  digitalWrite(MOTOR_ENABLE_PIN, LOW);
}

void loop() {

  on_off_switch_state = digitalRead(ON_OFF_SWITCH_PIN);
  delay(1);
  direction_switch_state = digitalRead(DIRECTION_CHANGE_PIN);
  motor_speed = analogRead(POT_PIN) / 4;

  Serial.print("speed: ");
  Serial.println(motor_speed);

  if (on_off_switch_state != previous_on_off_switch_state){
    if (on_off_switch_state == HIGH){
      motor_enabled = !motor_enabled;
    }
  }

  if(direction_switch_state != previous_direction_switch_state){
    if (direction_switch_state == HIGH){
      motor_direction = !motor_direction;
    }
  }

  // change direction of motor
  if (motor_direction == 1){
    digitalWrite(CONTROL_PIN_1, HIGH);
    digitalWrite(CONTROL_PIN_2, LOW);
  }
  else {
    digitalWrite(CONTROL_PIN_1, LOW);
    digitalWrite(CONTROL_PIN_2, HIGH);
  }

  // turn on/off motor and set speed
  if (motor_enabled == 1){
    analogWrite(MOTOR_ENABLE_PIN, motor_speed);
  }
  else {
    analogWrite(MOTOR_ENABLE_PIN, LOW);
  }

  previous_direction_switch_state = direction_switch_state;
  previous_on_off_switch_state = on_off_switch_state;
}

