
import numpy as np
import imageio
import math

import matplotlib.pyplot as plt

img = imageio.imread('assets/bw_small.jpg')
print(img.dtype)
np_img = img.astype(float)
print(np_img.dtype)

# np_img[0,20] = [0,180,180] #the 20th element on the first row. # to test the column first or row first

#blur
#I used the blur kernel from https://setosa.io/ev/image-kernels/
k_blur = np.array([[0.0625,0.125, 0.0625],
                   [0.125, 0.25, 0.125],
                   [0.0625, 0.125, 0.0625]])

# test the multiply function in np array
test_img = np_img[10,1]
print(test_img)  # [4. 4. 4.]
print(k_blur[0])  # [0.0625 0.125  0.0625]
test_result = test_img * k_blur[0]
print(test_result)  # [0.25 0.5  0.25]

# execute the blur keneral
blurImg = np_img.astype(float)
for i in range(1,np_img.shape[0]-1):
    for j in range(1,np_img.shape[1]-1):
        columnAboveR = np_img[i-1, j-1, 0] * k_blur[0,0] + np_img[i-1, j, 0] * k_blur[0,1]+ np_img[i-1, j+1, 0] * k_blur[0,2]
        columnAboveG = np_img[i-1, j-1, 1] * k_blur[0,0] + np_img[i-1, j, 1] * k_blur[0,1]+ np_img[i-1, j+1, 1] * k_blur[0,2]
        columnAboveB = np_img[i-1, j-1, 2] * k_blur[0,0] + np_img[i-1, j, 2] * k_blur[0,1]+ np_img[i-1, j+1, 2] * k_blur[0,2]
        columnHereR = np_img[i, j-1, 0] * k_blur[1,0] + np_img[i, j, 0] * k_blur[1,1]+ np_img[i, j+1, 0] * k_blur[1,2]
        columnHereG = np_img[i, j-1, 1] * k_blur[1,0] + np_img[i, j, 1] * k_blur[1,1]+ np_img[i, j+1, 1] * k_blur[1,2]
        columnHereB = np_img[i, j-1, 2] * k_blur[1,0] + np_img[i, j, 2] * k_blur[1,1]+ np_img[i, j+1, 2] * k_blur[1,2]
        columnBelowR = np_img[i+1, j-1, 0] * k_blur[2,0] + np_img[i+1, j, 0] * k_blur[2,1]+ np_img[i+1, j+1, 0] * k_blur[2,2]
        columnBelowG = np_img[i+1, j-1, 1] * k_blur[2,0] + np_img[i+1, j, 1] * k_blur[2,1]+ np_img[i+1, j+1, 1] * k_blur[2,2]
        columnBelowB = np_img[i+1, j-1, 2] * k_blur[2,0] + np_img[i+1, j, 2] * k_blur[2,1]+ np_img[i+1, j+1, 2] * k_blur[2,2]

        blurImg[i, j, 0] = columnAboveR + columnHereR + columnBelowR
        blurImg[i, j, 1] = columnAboveG + columnHereG + columnBelowG
        blurImg[i, j, 2] = columnAboveB + columnHereB + columnBelowB

        # end of for loop

plt.title('7-1 blur effect',fontsize=20)
# Show the original image
plt.subplot(1, 2, 1)
imgOut = np.uint8(np_img)
plt.imshow(imgOut)

# blurred image
plt.subplot(1, 2, 2)
blurImgOut = blurImg.astype(int)
blurOut = np.uint8(blurImg)
plt.imshow(blurOut)
plt.savefig("7-hw-blur-1.png")
plt.show()