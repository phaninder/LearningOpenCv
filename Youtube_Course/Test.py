import cv2
import numpy as np

img = cv2.imread("Clash.jpg")
img2 = np.copy(img)
shape = img.shape
print(shape[0]/2,shape[1]/2)
#cv2.line(img,(0,0),(shape[1]/2,shape[0]/2),(255,0,0))
#cv2.circle(img,(shape[1]/2,shape[0]/2+3),1,(0,0,0),-1)
cv2.rectangle(img,(shape[1]/2-2,shape[0]/2-1),(shape[1]/2+1,shape[0]/2+3),(0,0,0),-1)
cv2.ellipse(img,(shape[1]/2,shape[0]/2+3),(100,50),0,180,360,(0,0,0),-1)
cv2.imshow("Window",img)
cv2.imshow("Original",img2)
cv2.waitKey(0)
cv2.destroyAllWindows()