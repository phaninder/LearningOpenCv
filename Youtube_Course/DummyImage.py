import cv2
import numpy as np


road = cv2.imread("road.jpg")
car = cv2.imread("car.jpg")
car2 = cv2.cvtColor(car,cv2.COLOR_BGR2GRAY)
ret,mask = cv2.threshold(car2,240,255,cv2.THRESH_BINARY)
mask_inv = cv2.bitwise_not(mask)

car2 = cv2.bitwise_and(car,car,mask=mask_inv)
road2 = cv2.bitwise_and(road,road,mask=mask)
result = cv2.add(road2,car2)
cv2.imshow("Res",result)
cv2.imshow("Inv",car2)
cv2.imshow("Road",road2) 
cv2.waitKey(0)
cv2.destroyAllWindows()