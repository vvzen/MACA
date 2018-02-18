#*- coding: utf-8 *-
import time
import serial
from markov.markovchain import Markov

# serial communication
SERIAL_PORT = "/dev/cu.usbmodemFA131"
BAUD_RATE = 9600
board = serial.Serial(SERIAL_PORT, BAUD_RATE)

markov = Markov(order=2)
markov.train("motivational.txt")
sentence = markov.generate(5)

while True:
    received_message = board.readline().rstrip()
    print "received message: {}".format(received_message)

    if received_message == "start":
        serial_message = "{}".format(markov.generate(8))
        serial_message = serial_message.replace('’', "'").replace("…", "...").replace("”", "")
        #serial_message = "hello"
        print "sending message : {}".format(serial_message)
        board.write(serial_message)
    
    time.sleep(0.1)