# Importing the OpenCV library
import cv2
import numpy as np

# define a video capture object
cap = cv2.VideoCapture(0)

assert (cap.isOpened())

# Capture frame-by-frame
ret, frame = cap.read()
B, G, R = cv2.split(frame)
if ret:
    # Display the resulting frame
    cv2.imshow('Frame', frame)
    # waits for user to press any key
    # (this is necessary to avoid Python kernel from crashing)
    cv2.waitKey(0)

    cv2.imshow('Red', R)
    cv2.waitKey(0)

    cv2.imshow('Green', G)
    cv2.waitKey(0)


# When everything done, release
# the video capture object
cap.release()

# Closes all the frames
cv2.destroyAllWindows()
