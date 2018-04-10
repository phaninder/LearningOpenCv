import cv2
import numpy as np

img1= cv2.imread("Clash.jpg")
img2= cv2.imread("drawing_2.png")
img3 = cv2.bitwise_not(img1)
cv2.imshow("Drawing1",img1)
cv2.imshow("Drawing2",img3)
cv2.waitKey(0)
cv2.destroyAllWindows()