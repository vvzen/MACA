#!/bin/sh
echo "script was ran at" > runned.txt
date >> runned.txt
/usr/bin/python lcd_from_serial.py
