from matplotlib import pyplot as plt
import numpy as np
import math
myImage = np.zeros((10,10))

# change the color to 1(white) at position (5,5)
myImage[5,5]=1

plt.title('2 coloring one pixel',fontsize=20)
plt.imshow(myImage, cmap="gray", clim=(0, 1) )
plt.savefig("2-coloring-one-pixel.png")
plt.show()