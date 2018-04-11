import cv2
import numpy as np

blue = np.uint8([[[255,0,0]]])
bhsv = cv2.cvtColor(blue,cv2.COLOR_BGR2HSV)
print bhsv

cap = cv2.VideoCapture(0)

while True:
    _,frame=cap.read()
    
    hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    
    lower_blue = np.array([110,120,125])
    upper_blue = np.array([130,255,255])
    mask = cv2.inRange(hsv,lower_blue,upper_blue)
    
    result = cv2.bitwise_and(frame,frame,mask=mask)
    #cv2.imshow("Hsv",hsv)
    cv2.imshow("Mask",mask)
    cv2.imshow("Frame",frame)
    cv2.imshow("Res",result)
    
    key= cv2.waitKey(1)
    if key==27:
        break
cap.release()
cv2.destroyAllWindows()