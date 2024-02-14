import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

plt.rc("font", family="Inter")

data = np.random.rand(10, 10)
plt.imshow(data, cmap="winter")
plt.xlabel("Alice")
plt.ylabel("Evans")
plt.colorbar()
plt.title("Test Title")

plt.show()
