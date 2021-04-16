from matplotlib import pyplot as plt
import numpy as np
import math

# so numpy arrays are column major, not row major.
# So you need to do height first
myImage = np.zeros((240,320))

# This code is exactly the same as the the code
TWO_PI = 3.14159 * 2
segments = 20
spacing = TWO_PI / segments
size = 40
centre = 120

#draw a circle
for i in range(segments):
    x = math.cos(spacing * i) * size
    y = math.sin(spacing * i) * size
    myImage[math.floor(x) + 120, math.floor(y) + 160] = 1 # notice we need to floor the output to ints

#draw a saqure
for i in range(240):
    for j in range(320):
        if abs(centre-i) < size and abs(centre-j) < size:
            myImage[i,j]=1

plt.title('3 draw shapes',fontsize=20)
plt.imshow(myImage, interpolation="bilinear", clim=(0,1),cmap="gray")
plt.savefig("3-draw-shapes.png")
plt.show()

