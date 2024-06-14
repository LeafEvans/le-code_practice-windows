import numpy as np
import matplotlib.pyplot as plt
import numpy as np
from sklearn.datasets import load_iris
import matplotlib.pyplot as plt

# 加载鸢尾花数据集作为例子
iris = load_iris()
X = iris.data

# 数据中心化
X_centered = X - np.mean(X, axis=0)

# 计算协方差矩阵并进行特征值分解
C = np.cov(X_centered, rowvar=False)
eigenvalues, eigenvectors = np.linalg.eig(C)

# 选择前2个主成分
k = 2
P = eigenvectors[:, :k]

# 数据降维
Y = X_centered @ P

# 可视化
plt.figure(figsize=(12, 6))

# 降维前的数据可视化
plt.subplot(1, 2, 1)
plt.scatter(X[:, 0], X[:, 1], c=iris.target, cmap='viridis', alpha=0.6)
plt.title('Original Data (First Two Features)')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')

# 降维后的数据可视化
plt.subplot(1, 2, 2)
plt.scatter(Y[:, 0], Y[:, 1], c=iris.target, cmap='viridis', alpha=0.6)
plt.title(f'PCA Reduced Data (First Two Principal Components)')
plt.xlabel('PC1')
plt.ylabel('PC2')

plt.tight_layout()
plt.show()