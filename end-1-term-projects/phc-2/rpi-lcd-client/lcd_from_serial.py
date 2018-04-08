import serial
import re
import time
import Adafruit_CharLCD as LCD

# LCD STUFF
lcd_rs        = 25 
lcd_en        = 24
lcd_d4        = 23
lcd_d5        = 17
lcd_d6        = 18
lcd_d7        = 22
lcd_backlight = 4
lcd_columns   = 16
lcd_rows      = 2

# communication stuff
ser = serial.Serial(
    port="/dev/ttyAMA0",
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

display_regex = r"d:\w+"

def main():

    lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7, lcd_columns, lcd_rows, lcd_backlight)

    lcd.clear()
    lcd.set_cursor(0, 0)
    lcd.message("pi")
    lcd.set_cursor(1, 0)
    lcd.message("listenin")

    while True:
        current_message = ser.readline()
        #print current_message
        print "received a message from the udoo: {}".format(current_message)

        # if we get the ready message from the udoo
        # we know the connection is established, so then just print it to the display
        if current_message == "udooready":
            lcd.clear()
            lcd.set_cursor(0, 0)
            lcd.message("udoo ready")
            lcd.set_cursor(0, 1)
            lcd.message("pi ready")
        # if a message starts with d: , send this message to the lcd
        elif re.match(display_regex, current_message):
            lcd.clear()
            lcd.set_cursor(0, 0)
            lcd.message(current_message[2:])
            time.sleep(0.5)
    
if __name__ == "__main__":
    main()