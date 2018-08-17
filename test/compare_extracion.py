import numpy as np
import cv2
import argparse
from matplotlib import pyplot as plt

print(cv2.__version__)
print(np.zeros([1, 4]))
##
parser = argparse.ArgumentParser()
parser.add_argument('img_1', type=str)
parser.add_argument('img_2', type=str)
img = parser.parse_args()

img_1 = cv2.imread(img.img_1, cv2.IMREAD_COLOR)
img_2 = cv2.imread(img.img_2, cv2.IMREAD_COLOR)
# init
orb = cv2.ORB_create()

# find keypoint fast 
kp_1 = orb.detect(img_1, None)
kp_2 = orb.detect(img_2, None)
#
#find descriptor BRIST
kp_1, des_1 = orb.compute(img_1, kp_1)
kp_2, des_2 = orb.compute(img_2, kp_2)
#
#draw only keypoint location, not size and orientation
cv2.drawKeypoints(img_1, kp_1, img_1, color=(0, 255, 0), flags = 0)
cv2.drawKeypoints(img_2, kp_2, img_2, color=(0, 255, 0), flags = 0)
plt.imshow(img_1), plt.show()
plt.imshow(img_2), plt.show()
cv2.imwrite("img_keypoint_1.png", img_1)
cv2.imwrite("img_keypoint_2.png", img_2)
#
# create BFMatcher object
bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)

# Match descriptors
matches = bf.match(des_1, des_2)
#
# draw first 2
img_match = cv2.drawMatches(img_1, kp_1, img_2, kp_2, matches[:15], None, flags=2)
cv2.imwrite("img_match.png", img_match)
plt.imshow(img_match),plt.show()
cv2.waitKey(0)
#