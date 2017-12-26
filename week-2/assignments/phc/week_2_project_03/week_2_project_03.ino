// Pins used
#define TEMP_PIN A0
#define RED_LED_1 3
#define RED_LED_2 4
#define RED_LED_3 5

const float baseline_temp = 21;
int temp_sensor_value;
float voltage;
float temperature;

bool initialisation = true;

void setup() {

  // init serial communication
  Serial.begin(9600);
  // init pins
  pinMode(RED_LED_1, OUTPUT);
  pinMode(RED_LED_2, OUTPUT);
  pinMode(RED_LED_3, OUTPUT);
  // turn off leds
  digitalWrite(RED_LED_1, LOW);
  digitalWrite(RED_LED_2, LOW);
  digitalWrite(RED_LED_3, LOW);
}

void loop() {

  if (initialisation){
    for (int i = 0; i < 10; i++){
      digitalWrite(RED_LED_1, HIGH);
      digitalWrite(RED_LED_2, HIGH);
      digitalWrite(RED_LED_3, HIGH);
      delay(250);
      digitalWrite(RED_LED_1, LOW);
      digitalWrite(RED_LED_2, LOW);
      digitalWrite(RED_LED_3, LOW);
      delay(250);
    }
    initialisation = false;
  }

  temp_sensor_value = analogRead(TEMP_PIN);

  Serial.print("Sensor value: ");
  Serial.print(temp_sensor_value);

  // convert the sensor reading into voltage
  // sensor reading will go from 0 to 1024
  // so we'll remap it from 0 to 5 volts
  voltage = (temp_sensor_value / 1024.0) * 5.0;

  Serial.print(", Sensor voltage: ");
  Serial.print(voltage);

  // every ten millivolts there's a change of 1° Celsius
  temperature = (voltage - 0.5 ) * 100;
  Serial.print(", Degrees: ");
  Serial.println(temperature);

  // adjust leds based on temp
  if (temperature < baseline_temp){
    digitalWrite(RED_LED_1, LOW);
    digitalWrite(RED_LED_2, LOW);
    digitalWrite(RED_LED_3, LOW);
  }
  else if(temperature >= baseline_temp && temperature <= baseline_temp + 2){
    digitalWrite(RED_LED_1, HIGH);
    digitalWrite(RED_LED_2, LOW);
    digitalWrite(RED_LED_3, LOW);
  }
  else if(temperature > baseline_temp + 2 && temperature <= baseline_temp + 4){
    digitalWrite(RED_LED_1, HIGH);
    digitalWrite(RED_LED_2, HIGH);
    digitalWrite(RED_LED_3, LOW);
  }
  else if(temperature > baseline_temp + 4){
    digitalWrite(RED_LED_1, HIGH);
    digitalWrite(RED_LED_2, HIGH);
    digitalWrite(RED_LED_3, HIGH);
  }
  delay(20);
}
