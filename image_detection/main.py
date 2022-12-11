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
    GPIO.setup(pins.moveLeftPin, GPIO.OUT)
    GPIO.setup(pins.waterPin, GPIO.OUT)
    GPIO.setup(pins.moveRightPin, GPIO.OUT)
    GPIO.setup(pins.arduinoReadyPin, GPIO.IN) 


def sendCommand(pin):
    assert(pin in pins)

    GPIO.output(pin, True)
    time.sleep(1)
    GPIO.output(pin, False)

"""
The brain of the algorithm. Loops infinitely until powered off.
"""
def main():
    init()

    try: 
        while True:
            if GPIO.input(pins.arduinoReadyPin):
                filtered_img = img.detectColor(img.captureImage())

                sendCommand(pins.moveLeftPin)
            time.sleep(1)

    except KeyboardInterrupt:
        print("Expected program termination")
    except:
        print("Unexpected program termination")
    finally:
        GPIO.cleanup()  # Changes all pins back to inputs


main()
