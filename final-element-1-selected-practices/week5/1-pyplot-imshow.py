from matplotlib import pyplot as plt

from matplotlib import pyplot as plt
import numpy as np

# math!
import math

# randomly initialise an image 10 * 10 pixels
my_array = np.random.random((10,10))

# Also use 'full' or 'ones' or 'zeros'
# y = np.zeros((10,10)) # also try 'full((10,10),0.5)' or 'ones'
# my_array = np.full((10,10),0.9)

# cmap sets the colourmap - https://matplotlib.org/examples/color/colormaps_reference.html
# cmap is ignored for datasets with rank of 3 or 4, as these are assumed to be RGB(a)
# interpolation is used when the number of pixels in the array
# is such that it can't be shown properly given the size of the plot
# you need to set the lower and upper limits with clim !!!


plt.title('1 simple random grayscale',fontsize=20)
plt.imshow(my_array,  cmap='gray', clim=(0,1))
plt.savefig("1-pyplot-imshow.png")
plt.show()