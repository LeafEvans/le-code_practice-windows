import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

# 设置字体为宋体
plt.rcParams['font.sans-serif'] = ['FangSong']  # 设置字体为宋体
plt.rcParams['axes.unicode_minus'] = False  # 解决负号显示问题

# 生成一些示例数据
np.random.seed(10)
data = [np.random.normal(0, std, 100) for std in range(1, 4)]

# 转换为pandas DataFrame
import pandas as pd

df = pd.DataFrame({
    'Category':
    ['Category 1'] * 100 + ['Category 2'] * 100 + ['Category 3'] * 100,
    'Value':
    np.concatenate(data)
})

# 使用 Seaborn 绘制横向大提琴图
sns.violinplot(x='Value', y='Category', data=df)
plt.title('横向大提琴图')
plt.xlabel('值')
plt.ylabel('类别')
plt.show()
