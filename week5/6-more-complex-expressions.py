from matplotlib import pyplot as plt
import numpy as np
import math

myImage = np.zeros((240,320))
PI = 3.14159

width_frequency = 3.14159 / 320

frequency = width_frequency * 500#5000

for i in range(240):
    for j in range(320):
        #original example
        #t = math.tan(i / frequency) * math.cos(j / frequency) + math.atan(j / frequency) * math.cos(i / frequency)
        #my twist
        t = math.tan(i / frequency) * math.cos(i / frequency) + math.tan(j / frequency) * math.sin(j / frequency)
        myImage[i,j]=t
plt.title('6 more complex expressions',fontsize=20)
plt.imshow(myImage, clim=(0,1),cmap="gray")
plt.imshow(myImage, interpolation="bilinear", clim=(0,1),cmap="gray")
plt.savefig("6-more-complex-expressions.png")
plt.show()