import numpy as np
import cv2
import argparse
import matplotlib import pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument('dir', type=str)
parser.add_argument('img_1', type=str)
parser.add_argument('img_2', type=str)
parser.add_argument('img_3', type=str)
parser.add_argument('img_4', type=str)
parser.add_argument('img_5', type=str)
parser.add_argument('img_6', type=str)
img = parser.parse_args()

img_1 = cv2.imread(dir+img.img_1+'.png', cv2.IMREAD_COLOR)
img_2 = cv2.imread(dir+img.img_2+'.png', cv2.IMREAD_COLOR)
img_3 = cv2.imread(dir+img.img_3+'.png', cv2.IMREAD_COLOR)
img_4 = cv2.imread(dir+img.img_4+'.png', cv2.IMREAD_COLOR)
img_5 = cv2.imread(dir+img.img_5+'.png', cv2.IMREAD_COLOR)
img_6 = cv2.imread(dir+img.img_6+'.png', cv2.IMREAD_COLOR)
arr = [img_1, img_2, img_3, img_4, img_5, img_6]

toImage = Image.new('RGB', ())