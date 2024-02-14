import numpy as np

a = np.array([1, 2, 3, 4])
print(a)
print(np.average(a))

wts = np.array([4, 3, 2, 1])
print(np.average(a, weights=wts))

print(np.average([1, 2, 3, 4], weights=[4, 3, 2, 1], returned=True))
