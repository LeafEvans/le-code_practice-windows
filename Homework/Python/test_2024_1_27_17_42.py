import matplotlib.pyplot as plt
import numpy as np

plt.rc("font",style="italic")

n = 4

matrix = np.reshape(np.linspace(0, 1, n**2), (n, n))

plt.figure(figsize=(12, 4.5))

ax1 = plt.subplot(1, 3, 1)
im1 = ax1.imshow(matrix, cmap="viridis", interpolation="bessel")
plt.xticks(range(n))
plt.yticks(range(n))
plt.title("Gray Color Map")

ax2 = plt.subplot(1, 3, 2)
im2 = ax2.imshow(matrix, cmap="viridis", interpolation="bilinear")
plt.yticks([])
plt.xticks(range(n))
plt.title("Viridis Color Map")

ax3 = plt.subplot(1, 3, 3)
im3 = ax3.imshow(matrix, cmap="viridis", interpolation="bicubic")
plt.yticks([])
plt.xticks(range(n))
plt.title("Viridis Color Map")

# 计算最小值和最大值
vmin = np.min([im1.get_array().min(), im2.get_array().min(), im3.get_array().min()])
vmax = np.max([im1.get_array().max(), im2.get_array().max(), im3.get_array().max()])

# 创建 colorbar
plt.colorbar(im3, ax=[ax1, ax2, ax3], ticks=np.linspace(vmin, vmax, num=4))

plt.show()
