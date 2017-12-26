// PINS
// rgb led
#define RED_LED 11
#define GREEN_LED 10
#define BLUE_LED 9
// photoresistors
#define RED_SENSOR A0
#define GREEN_SENSOR A1
#define BLUE_SENSOR A2
// measure values
int red_sensor_value = 0;
int green_sensor_value = 0;
int blue_sensor_value = 0;
int red_value = 0;
int green_value = 0;
int blue_value = 0;

bool initialising = true;

void setup() {

  // init serial communication
  Serial.begin(9600);
  // init pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

void loop() {

  if (initialising){

    for (int i = 0; i < 10; i++){
      analogWrite(RED_LED, 255);
      analogWrite(GREEN_LED, 0);
      analogWrite(BLUE_LED, 0);
      delay(500);
      analogWrite(RED_LED, 0);
      analogWrite(GREEN_LED, 255);
      analogWrite(BLUE_LED, 0);
      delay(500);
      analogWrite(RED_LED, 0);
      analogWrite(GREEN_LED, 0);
      analogWrite(BLUE_LED, 255);
      delay(500);
    }
    
    initialising = false;
  }

  red_sensor_value = analogRead(RED_SENSOR);
  // put a small delay in order to take account of the ADC work
  delay(5);
  green_sensor_value = analogRead(GREEN_SENSOR);
  delay(5);
  blue_sensor_value = analogRead(BLUE_SENSOR);

  Serial.print("Raw sensor values:\tRed: ");
  Serial.print(red_sensor_value);
  Serial.print("\tGreen: ");
  Serial.print(green_sensor_value);
  Serial.print("\tBlue: ");
  Serial.println(blue_sensor_value);

  red_value = red_sensor_value / 4;
  green_value = green_sensor_value / 4;
  blue_value = blue_sensor_value / 4;

  Serial.print("Mapped sensor values:\tRed: ");
  Serial.print(red_value);
  Serial.print("\tGreen: ");
  Serial.print(green_value);
  Serial.print("\tBlue: ");
  Serial.print(blue_value);

  // use pwm to alter the color of the RGB led
  analogWrite(RED_LED, red_value);
  analogWrite(GREEN_LED, green_value);
  analogWrite(BLUE_LED, blue_value);
}
