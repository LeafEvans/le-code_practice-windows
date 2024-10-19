import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


class KMeans:

    def __init__(self, data, num_clustres):
        self.data = data
        self.num_clustres = num_clustres

    def train(self, max_iterations):
        centroids = KMeans.centroids_init(self.data, self.num_clustres)
        num_examples = self.data.shape[0]
        closest_centroids_ids = np.empty((num_examples, 1))

        for _ in range(max_iterations):
            closest_centroids_ids = KMeans.centroids_find_closest(
                self.data, centroids)
            centroids = KMeans.centroids_compute(self.data,
                                                 closest_centroids_ids,
                                                 self.num_clustres)
        return centroids, closest_centroids_ids

    @staticmethod
    def centroids_init(data, num_clustres):
        num_examples = data.shape[0]
        random_ids = np.random.permutation(num_examples)
        centroids = data[random_ids[:num_clustres], :]
        return centroids

    @staticmethod
    def centroids_find_closest(data, centroids):
        num_examples = data.shape[0]
        num_centroids = centroids.shape[0]
        closest_centroids_ids = np.zeros((num_examples, 1))
        for example_index in range(num_examples):
            distance = np.zeros((num_centroids, 1))
            for centroid_index in range(num_centroids):
                distance_diff = data[example_index, :] - centroids[
                    centroid_index, :]
                distance[centroid_index] = np.sum(distance_diff**2)
            closest_centroids_ids[example_index] = np.argmin(distance)
        return closest_centroids_ids

    @staticmethod
    def centroids_compute(data, closest_centroids_ids, num_clustres):
        num_features = data.shape[1]
        centroids = np.zeros((num_clustres, num_features))
        for centroids_id in range(num_clustres):
            closest_ids = closest_centroids_ids == centroids_id
            centroids[centroids_id, :] = np.mean(
                data[closest_ids.flatten(), :], axis=0)
        return centroids


data = pd.read_csv('../data/iris.csv')
iris_types = ['SETOSA', 'VERESCOLOR', 'VIRGINICA']

x_axis = 'petal_length'
y_axis = 'petal_width'

plt.figure(figsize=(12, 5))
plt.subplot(1, 2, 1)

for iris_type in iris_types:
    plt.scatter(
        data[x_axis][data['class'] == iris_type],
        data[y_axis][data['class'] == iris_type],
        label=iris_type,
    )
plt.title('Label Known')
plt.legend()

plt.subplot(1, 2, 2)
plt.scatter(data[x_axis][:], data[y_axis][:])
plt.title('Label Unknown')
plt.show()

num_examples = data.shape[0]
x_train = data[[x_axis, y_axis]].values

num_clustres = 3
max_iterations = 50

k_means = KMeans(x_train, num_clustres)
centroids, closest_centroids_ids = k_means.train(max_iterations)

plt.figure(figsize=(12, 5))
plt.subplot(1, 2, 1)

for iris_type in iris_types:
    plt.scatter(
        data[x_axis][data['class'] == iris_type],
        data[y_axis][data['class'] == iris_type],
        label=iris_type,
    )
plt.title('Label Known')
plt.legend()

plt.subplot(1, 2, 2)
for centroid_id, centroid in enumerate(centroids):
    current_examples_index = (closest_centroids_ids == centroid_id).flatten()
    plt.scatter(
        x_train[current_examples_index, 0],
        x_train[current_examples_index, 1],
        label=centroid_id,
    )

for centroid_id, centroid in enumerate(centroids):
    plt.scatter(centroid[0], centroid[1], c='k', marker='*')

plt.title('Label Kmeans')

plt.show()
