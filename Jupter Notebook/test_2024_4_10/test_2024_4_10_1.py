import numpy as np
import matplotlib.pyplot as plt

# 数据
labels = np.array(['A', 'B', 'C', 'D', 'E'])  # 标签
stats = np.array([20, 34, 30, 35, 27])  # 数据值

# 角度设置
angles = np.linspace(0, 2 * np.pi, len(labels), endpoint=False).tolist()

# 闭合图形
stats = np.concatenate((stats,[stats[0]]))
angles += angles[:1]

# 绘图
fig, ax = plt.subplots(figsize=(6, 6), subplot_kw=dict(polar=True))
ax.fill(angles, stats, color='blue', alpha=0.25)
ax.plot(angles, stats, color='blue', linewidth=2)  # 连接线
ax.set_yticklabels([])  # 隐藏半径标签

# 添加标签
ax.set_xticks(angles[:-1])
ax.set_xticklabels(labels)



plt.show()
