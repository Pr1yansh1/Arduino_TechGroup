import RPi.GPIO as GPIO
import time
import cv2

"""
GPIO.setmode(GPIO.BOARD)
GPIO.setup(7, GPIO.OUT)

for i in range(5):
    GPIO.output(7, True)
    time.sleep(1)
    GPIO.output(7, False)
    time.sleep(1)
GPIO.cleanup()
"""

cap = cv2.VideoCapture(0)
assert(cap.isOpened())
ret, frame = cap.read()
if ret:
    cv2.imshow('BlairShco', frame)
    cv2.waitKey(0)

