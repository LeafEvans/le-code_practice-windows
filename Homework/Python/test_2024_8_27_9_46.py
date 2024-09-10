import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.datasets import make_blobs


# 绘制数据点的函数
def plot_data(X):
    plt.scatter(X[:, 0], X[:, 1], color='k', s=2)  # 使用 plt.scatter 而不是 plt.plot


# 绘制质心的函数
def plot_centroids(centroids, weights=None, circle_color='w', cross_color='k'):
    if weights is not None:
        selected_centroids = centroids[weights > weights.max() / 10]
    else:
        selected_centroids = centroids

    plt.scatter(
        selected_centroids[:, 0],
        selected_centroids[:, 1],
        marker='o',
        s=30,
        linewidths=8,
        color=circle_color,
        zorder=10,
        alpha=0.9,
    )
    plt.scatter(
        selected_centroids[:, 0],
        selected_centroids[:, 1],
        marker='x',
        s=50,
        linewidths=2,  # 改为更合理的值
        color=cross_color,
        zorder=11,
        alpha=1,
    )


# 绘制决策边界的函数
def plot_decision_boundaries(
    clusterer,
    X,
    resolution=1000,
    show_centroids=True,
    show_xlabels=True,
    show_ylabels=True,
):
    mins = X.min(axis=0) - 0.1
    maxs = X.max(axis=0) + 0.1
    xx, yy = np.meshgrid(
        np.linspace(mins[0], maxs[0], resolution),
        np.linspace(mins[1], maxs[1], resolution),
    )
    Z = clusterer.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)

    plt.contourf(Z, extent=(mins[0], maxs[0], mins[1], maxs[1]), cmap='Pastel2')
    plt.contour(
        Z, extent=(mins[0], maxs[0], mins[1], maxs[1]), linewidths=1, colors='k'
    )

    plot_data(X)

    if show_centroids:
        plot_centroids(clusterer.cluster_centers_)

    if show_xlabels:
        plt.xlabel('$x_1$', fontsize=14)
    else:
        plt.tick_params(labelbottom='off')

    if show_ylabels:
        plt.ylabel('$x_2$', fontsize=14, rotation=0)
    else:
        plt.tick_params(labelleft='off')

    plt.show()  # 显示图形


# 生成示例数据
X, _ = make_blobs(n_samples=1000, centers=4, cluster_std=0.6, random_state=42)

# 训练 KMeans 模型
kmeans_iter1 = KMeans(
    n_clusters=4, init='random', n_init=1, max_iter=1, random_state=42
).fit(X)
kmeans_iter2 = KMeans(
    n_clusters=4,
    init=kmeans_iter1.cluster_centers_,
    n_init=1,
    max_iter=2,
    random_state=42,
).fit(X)
kmeans_iter3 = KMeans(
    n_clusters=4,
    init=kmeans_iter2.cluster_centers_,
    n_init=1,
    max_iter=3,
    random_state=42,
).fit(X)

# 绘制子图
plt.figure(figsize=(10, 8))

plt.subplot(3, 2, 1)
plot_data(X)
plot_centroids(kmeans_iter1.cluster_centers_, circle_color='r', cross_color='k')
plt.title('Update Cluster Centers')

plt.subplot(3, 2, 2)
plot_decision_boundaries(kmeans_iter1, X, show_xlabels=False, show_ylabels=False)
plt.title('Label')

plt.subplot(3, 2, 3)
plot_decision_boundaries(kmeans_iter1, X, show_xlabels=False, show_ylabels=False)
plot_centroids(kmeans_iter2.cluster_centers_)

plt.subplot(3, 2, 4)
plot_decision_boundaries(kmeans_iter2, X, show_xlabels=False, show_ylabels=False)

plt.subplot(3, 2, 5)
plot_decision_boundaries(kmeans_iter2, X, show_xlabels=False, show_ylabels=False)
plot_centroids(kmeans_iter3.cluster_centers_)

plt.subplot(3, 2, 6)
plot_decision_boundaries(kmeans_iter3, X, show_xlabels=False, show_ylabels=False)

plt.tight_layout()
plt.show()
