#include <LiquidCrystal.h>

// PINS
#define SWITCH_PIN 6

int switch_state = 0;
int previous_switch_state = 0;
int reply;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {

  lcd.begin(16, 2);
  pinMode(SWITCH_PIN, INPUT);

  lcd.print("Ask the");
  lcd.setCursor(0, 1);
  lcd.print("Crystal ball");

}

void loop() {

  switch_state = digitalRead(SWITCH_PIN);

  if (switch_state != previous_switch_state){
    if (switch_state == LOW){
      reply = random(8);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The ball says:");
      lcd.setCursor(0, 1);

      switch (reply){
        case 0: {
          lcd.print("Yes");
          break;
        }
        case 1: {
          lcd.print("Most likely");
          break;
        }
        case 2: {
          lcd.print("Certainly");
          break;
        }
        case 3: {
          lcd.print("Outlook good");
          break;
        }
        case 4: {
          lcd.print("Unsure");
          break;
        }
        case 5: {
          lcd.print("Ask again");
          break;
        }
        case 6: {
          lcd.print("Doubtful");
          break;
        }
        case 7: {
          lcd.print("No");
          break;
        }
      } 
    }
  }
  
  previous_switch_state = switch_state;
}
