# Importing the OpenCV library
import cv2
import numpy as np
import serial
import time

def sendCoordinate(port):
    # port = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    # port.reset_input_buffer()
    while "Shco" not in line:
        port.write(b"x7y9\n")
        line = port.readline().decode('utf-8').rstrip()
        print(line)
        time.sleep(1)


"""
Capture an image from webcam and return frame (NumPy array)
"""
def captureImage():
    # define a video capture object
    cap = cv2.VideoCapture(0)

    assert (cap.isOpened())

    # Capture frame-by-frame
    ret, frame = cap.read()

    # When everything done, release
    # the video capture object
    cap.release()

    return frame


"""
Given an image, return filtered (only green) parts
Code from https://pyimagesearch.com/2014/08/04/opencv-python-color-detection/
"""
def detectColor(image):

    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    mask = cv2.inRange(hsv, (36, 25, 25), (70, 255, 255))
    imask = mask > 0
    green = np.zeros_like(image, np.uint8)
    green[imask] = image[imask]
    cv2.imshow("images", np.hstack([image, green]))
    cv2.waitKey(0)

    return green
    

port = serial.Serial('/dev/cu.usbmodem1301', 9600, timeout=1)
port.reset_input_buffer()
sendCoordinate(port)