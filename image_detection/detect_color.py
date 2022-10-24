# code used from https://pyimagesearch.com/2014/08/04/opencv-python-color-detection/
import numpy as np
import argparse
import cv2

ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", help = "path to image")
args = vars(ap.parse_args())
# load the image
image = cv2.imread(args["image"])

boundaries = [([0, 0, 0], [100, 255, 75])]

(lower, upper) = boundaries[0]
lower = np.array(lower, dtype = "uint8")
upper = np.array(upper, dtype = "uint8")

mask = cv2.inRange(image, lower, upper)
output = cv2.bitwise_and(image, image, mask = mask)
print(mask)
print(output)

cv2.imshow("images", np.hstack([image, output]))
cv2.waitKey(0)