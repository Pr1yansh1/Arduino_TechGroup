# Importing the OpenCV library
import cv2
import numpy as np

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
    boundaries = [([0, 0, 0], [100, 255, 75])]

    (lower, upper) = boundaries[0]
    lower = np.array(lower, dtype = "uint8")
    upper = np.array(upper, dtype = "uint8")

    mask = cv2.inRange(image, lower, upper)
    output = cv2.bitwise_and(image, image, mask = mask)

    cv2.imshow("images", np.hstack([image, output]))
    cv2.waitKey(0)

    return output
      