import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

class KMeans:
    """K-means聚类算法实现"""
    
    def __init__(self, data, num_clusters):
        self.data = data
        self.num_clusters = num_clusters
        self.centroids = None
        self.labels = None

    def train(self, max_iterations):
        # 初始化质心
        self.centroids = self._init_centroids()
        
        for _ in range(max_iterations):
            # E步:分配样本到最近的质心
            self.labels = self._assign_clusters()
            # M步:重新计算质心
            new_centroids = self._update_centroids()
            
            # 判断是否收敛
            if np.allclose(self.centroids, new_centroids):
                break
                
            self.centroids = new_centroids
            
        return self.centroids, self.labels

    def _init_centroids(self):
        """随机初始化质心"""
        num_examples = self.data.shape[0]
        random_indices = np.random.permutation(num_examples)
        return self.data[random_indices[:self.num_clusters], :]

    def _assign_clusters(self):
        """为每个样本分配最近的质心"""
        distances = np.sqrt(((self.data[:, np.newaxis] - self.centroids) ** 2).sum(axis=2))
        return np.argmin(distances, axis=1).reshape(-1, 1)

    def _update_centroids(self):
        """更新质心位置"""
        new_centroids = np.zeros((self.num_clusters, self.data.shape[1]))
        for k in range(self.num_clusters):
            mask = (self.labels == k).flatten()
            if np.any(mask):
                new_centroids[k] = np.mean(self.data[mask], axis=0)
            else:
                new_centroids[k] = self.centroids[k]
        return new_centroids

def plot_clusters(data, x_axis, y_axis, iris_types=None, labels=None, centroids=None):
    """绘制聚类结果"""
    plt.figure(figsize=(12, 5))
    
    # 绘制原始数据分布
    plt.subplot(1, 2, 1)
    if iris_types is not None:
        for iris_type in iris_types:
            plt.scatter(
                data[x_axis][data['class'] == iris_type],
                data[y_axis][data['class'] == iris_type],
                label=iris_type
            )
        plt.title('已知标签分布')
    plt.legend()
    
    # 绘制聚类结果
    plt.subplot(1, 2, 2)
    if labels is not None and centroids is not None:
        x_train = data[[x_axis, y_axis]].values
        for k in range(len(centroids)):
            mask = (labels == k).flatten()
            plt.scatter(
                x_train[mask, 0],
                x_train[mask, 1],
                label=f'簇 {k+1}'
            )
        # 绘制质心
        plt.scatter(centroids[:, 0], centroids[:, 1], 
                   c='red', marker='*', s=200, label='质心')
        plt.title('K-means聚类结果')
    plt.legend()
    
    plt.tight_layout()
    plt.show()

# 加载数据
data = pd.read_csv('../data/iris.csv')
iris_types = ['SETOSA', 'VERESCOLOR', 'VIRGINICA']

# 选择特征
x_axis = 'petal_length'
y_axis = 'petal_width'

# 显示原始数据分布
plot_clusters(data, x_axis, y_axis, iris_types)

# 准备训练数据
x_train = data[[x_axis, y_axis]].values
num_clusters = 3
max_iterations = 50

# 训练模型
kmeans = KMeans(x_train, num_clusters)
centroids, labels = kmeans.train(max_iterations)

# 显示聚类结果
plot_clusters(data, x_axis, y_axis, iris_types, labels, centroids)
