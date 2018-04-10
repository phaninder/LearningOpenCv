import cv2
import numpy as np

x= 0
def changed(y):
    global x
    x=y
    
cap = cv2.VideoCapture(0)

cv2.namedWindow("Frame")
cv2.createTrackbar("Test","Frame",0,1,changed)

while True:
    _,frame=cap.read()
    
   
    if x==1:
        frame = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    else:
        pass
    
    cv2.imshow("Frame",frame)
    key=cv2.waitKey(1)
    if key==27:
        break
cap.release()
cv2.destroyAllWindows()