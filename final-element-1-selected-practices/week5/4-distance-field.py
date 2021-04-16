from matplotlib import pyplot as plt
import numpy as np
import math

myImage = np.zeros((240,320))
myImage2 = np.zeros((240,320))

centre = 100
size = 50

# distance field to draw a circle
for i in range(240):
    for j in range(320):
        x_dist = abs(centre-i)
        y_dist = abs(centre-j)
        dist = math.sqrt(x_dist * x_dist + y_dist * y_dist)
        if dist < size:
            myImage[i,j] = 1


# use built in numpy distance functions to draw a circle
centre2 = 100
size2 = 50
for i in range(240):
    for j in range(320):
        position=np.array([[i,j],[abs(centre2-i),abs(centre2-j)]])
        distance = np.linalg.norm(position[0:1] - position[1:2])
        if distance < size2:
            myImage[i,j] = 0.5

plt.title('4 distance field',fontsize=20)
plt.imshow(myImage, clim=(0,1),cmap="gray")
plt.imshow(myImage, interpolation="bilinear", clim=(0,1), cmap="gray")
plt.savefig("4-distance-field.png")
plt.show()
