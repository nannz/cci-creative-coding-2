from matplotlib import pyplot as plt
import numpy as np
import math

myImage = np.zeros((240,320))  # column first

width_frequency = 3.14159/240

frequency = width_frequency * 10

for i in range(240):
    for j in range(320):
        #I twisted the code here. Originally the sin wave's centre starts from (0,0)
        #I changed the index number from (0-240) to (-120 - 120), same change on j.
        #So the graph shows growing from the center.
        ii = i - 120
        jj = j - 160
        t = math.sin(math.sqrt(ii * ii + jj * jj) * frequency)
        myImage[i,j]=t
plt.title('5 complex expressions',fontsize=20)
plt.imshow(myImage, clim=(0,1),cmap="gray")
plt.imshow(myImage, interpolation="bilinear", clim=(0,1),cmap="gray")
plt.savefig("5-complex-expressions.png")
plt.show()