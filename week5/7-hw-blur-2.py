# Try gaussian blur and another way to execute the blur effect.
# Two gaussain blur kernels:
# 1. https://aishack.in/tutorials/image-convolution-examples/
# 2. https://en.wikipedia.org/wiki/Kernel_(image_processing)

import numpy as np
import imageio
import math
import matplotlib.pyplot as plt

img = imageio.imread('assets/bw_small.jpg')
np_img = img.astype(float)

k_gaublur = np.array([[1 / 256, 4  / 256,  6 / 256,  4 / 256, 1 / 256],
                   [4 / 256, 16 / 256, 24 / 256, 16 / 256, 4 / 256],
                   [6 / 256, 24 / 256, 36 / 256, 24 / 256, 6 / 256],
                   [4 / 256, 16 / 256, 24 / 256, 16 / 256, 4 / 256],
                   [1 / 256, 4  / 256,  6 / 256,  4 / 256, 1 / 256]])

blurImg = np_img.astype(float)
offset = int(math.floor(k_gaublur.shape[0]/2))
for i in range(offset,np_img.shape[0]-offset):
    for j in range(offset, np_img.shape[1] - offset):
        temp = np.zeros(3)
        # try another way to compute blur
        for a in range(k_gaublur.shape[0]):
            for b in range(k_gaublur.shape[1]):
                ia = i + a - offset
                jb = j + b - offset
                rgb = np_img[ia,jb]
                temp[0] += np_img[ia,jb,0] * k_gaublur[a,b]
                temp[1] += np_img[ia, jb, 1] * k_gaublur[a, b]
                temp[2] += np_img[ia, jb, 2] * k_gaublur[a, b]
        blurImg[i,j] = temp.copy() # copy just in case

plt.title('7-2 gaussian blur',fontsize=20)
# Show the original image
plt.subplot(1, 2, 1)
imgOut = np.uint8(np_img)
plt.imshow(imgOut)

# blur
plt.subplot(1, 2, 2)
blurImgOut = blurImg.astype(int)
blurOut = np.uint8(blurImg)
plt.imshow(blurOut)
plt.savefig("7-hw-blur-2.png")
plt.show()