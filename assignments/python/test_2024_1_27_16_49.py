import matplotlib.pyplot as plt
import numpy as np

plt.rc("font", family="Inter")

x = np.array(["Trump", "Jack", "Jacy", "Alice"])
y = np.array([12, 34, 54, 21])

plt.barh(x, y, color=["#4CAF50", "red", "hotpink", "#556B2F"], height=0.5)
plt.show()
