import numpy as np


def log_centered_ratio_transform(data):
    D = data.shape[0]
    g = (np.prod(data)) ** (1 / (D - 1))
    transformed_data = np.zeros(D - 1)
    for i in range(1, D):
        y = data[i] / g
        transformed_data[i - 1] = np.log(y)
    return transformed_data


data = np.array([0.2, 0.3, 0.1, 0.4])
transformed = log_centered_ratio_transform(data)
print(transformed)
