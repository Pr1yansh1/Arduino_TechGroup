"""
TODO:
0. Setup SSH config on Raspberry Pi
1. Wire up Raspberry Pi to Arduino Uno (need to change Uno Code)
2. Need to improve imaging algorithm by a lot lol...
"""

import RPi.GPIO as GPIO
import time
from enum import Enum

import imageDetection as img

# Pin setup for a Raspberry Pi 3 A
class pins(Enum):
    moveLeftPin = 11  # GPIO 17: Tell Arduino to move left
    waterPin = 13  # GPIO 27: Tell Arduino to water
    moveRightPin = 15  # GPIO 22: Tell Arduino to move right

    arduinoReadyPin = 16  # GPIO 23: Arduino is ready to take next decision


"""
Initialize pins.
"""
def init():
    GPIO.setmode(GPIO.BOARD)
    # The following are all active high inputs and outputs
    GPIO.setup(pins.moveLeftPin.value, GPIO.OUT)
    GPIO.setup(pins.waterPin.value, GPIO.OUT)
    GPIO.setup(pins.moveRightPin.value, GPIO.OUT)
    GPIO.setup(pins.arduinoReadyPin.value, GPIO.IN) 


def sendCommand(pin):
    assert(pin in pins)

    GPIO.output(pin.value, True)
    time.sleep(1)
    GPIO.output(pin.value, False)


"""
The brain of the algorithm. Loops infinitely until powered off.
"""
def main():
    init()

    try: 
        while True:
            if True:  # GPIO.input(pins.arduinoReadyPin.value):
                original_img = img.captureImage()
                filtered_img = img.detectColor(original_img)

                sendCommand(pins.moveLeftPin)
            time.sleep(1)

    except KeyboardInterrupt:
        print("Expected program termination")
    except Exception as e:
        print(e)
    finally:
        GPIO.cleanup()  # Changes all pins back to inputs


main()
