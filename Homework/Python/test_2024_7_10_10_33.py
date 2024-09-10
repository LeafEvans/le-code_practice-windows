import numpy as np

class KMeans:
    def __init__(self, data, num_clustres):
        self.data = data 
        self.num_clustres = num_clustres 

    def train(self, max_iterations):
        centroids = KMeans.centroids_init(self.data, self.num_clustres)
        num_examples = self.data.shape[0]
        closest_centroids_ids = np.empty((num_examples, 1))
        for _ in range(max_iterations):
            closest_centroids_ids = KMeans.centroids_find_closest(self.data, centroids)
            centroids = KMeans.centroids_compute(self.data, closest_centroids_ids)
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
                distance_diff = data[example_index, :]
                distance[centroid_index] = sum(distance_diff**2)
            closest_centroids_ids = np.argmin(distance)
        return closest_centroids_ids 
    
    @staticmethod
    def centroids_compute(data, closest_centroids_ids, num_clustres):
        num_features = data.shape[1]
        centroids = np.zeros((num_clustres, num_features))
        for centroids_id in range(num_clustres):
            closest_ids = closest_centroids_ids == centroids_id
            centroids[closest_ids] = np.mean(data[closest_ids.fallten(), :], axis=0)
        return centroids
        