import numpy as np

a = np.arange(6).reshape(2, 3)
print(a, "\n")
for _ in np.nditer(a):
    print(_, end=",")
print("\n")
