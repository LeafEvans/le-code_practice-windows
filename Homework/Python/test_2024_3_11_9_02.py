import numpy as np

a = np.array([[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]])
print(len(a))
print(a.shape)
a = np.array([1, 2, 3])
print(a)
print(len(a))
print(-1 * a)
b = a
print(a * b)
print(a @ b)
