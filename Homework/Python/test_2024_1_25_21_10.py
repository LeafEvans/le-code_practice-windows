import matplotlib.pyplot as plt
import numpy as np


plt.rc("font", family="Inter")

# 数据和对应的颜色
data = {
    "1 try": 12,
    "2 tries": 6,
    "3 tries": 22,
    "4 tries": 32,
    "5 tries": 23,
    "6 tries": 12,
    "7+ tries": 4,
}
colors = plt.cm.get_cmap("tab20c")(np.linspace(0, 1, len(data)))

# 提取标签和数据值
labels = data.keys()
sizes = data.values()

# 创建并配置图表
fig, ax = plt.subplots(figsize=(8, 8), subplot_kw={"aspect": "equal"})
wedges, texts = ax.pie(sizes, colors=colors, startangle=90, wedgeprops=dict(width=0.3))

# 隐藏饼图内部的百分比标签
for text in texts:
    text.set_visible(False)

# 计算每个部分的百分比，并创建图例标签
percentages = [(size / sum(sizes)) * 100 for size in sizes]
legend_labels = [f"{label}: {pct:.1f}%" for label, pct in zip(labels, percentages)]

# 添加中心圆圈
centre_circle = plt.Circle((0, 0), 0.70, fc=(0.95, 0.95, 0.95), alpha=0.8)
ax.add_artist(centre_circle)

# 设置标题
ax.set_title('Predicted Result of "EERIE"', fontweight="bold")

# 创建并添加图例
patches = [plt.Rectangle((0, 0), 1, 1, color=color) for color in colors]
ax.legend(
    patches,
    legend_labels,
    loc="upper left",
    bbox_to_anchor=(1, 1),
    title="Attempts and Percentages",
)

# 显示图形
plt.tight_layout()
plt.show()
