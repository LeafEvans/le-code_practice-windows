import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

# 创建立方体的顶点
vertices = np.array([
    [0, 0, 0],  # 顶点0
    [1, 0, 0],  # 顶点1 
    [1, 1, 0],  # 顶点2
    [0, 1, 0],  # 顶点3
    [0, 0, 1],  # 顶点4
    [1, 0, 1],  # 顶点5
    [1, 1, 1],  # 顶点6
    [0, 1, 1]   # 顶点7
])

# 定义立方体的边
edges = [
    [0, 1], [1, 2], [2, 3], [3, 0],  # 底面
    [4, 5], [5, 6], [6, 7], [7, 4],  # 顶面
    [0, 4], [1, 5], [2, 6], [3, 7]   # 连接线
]

# 创建3D图形
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# 绘制边
for edge in edges:
    x = [vertices[edge[0]][0], vertices[edge[1]][0]]
    y = [vertices[edge[0]][1], vertices[edge[1]][1]]
    z = [vertices[edge[0]][2], vertices[edge[1]][2]]
    ax.plot(x, y, z, 'b')

# 设置标题和标签
ax.set_title('立方体')
ax.set_xlabel('X轴')
ax.set_ylabel('Y轴')
ax.set_zlabel('Z轴')

plt.show()