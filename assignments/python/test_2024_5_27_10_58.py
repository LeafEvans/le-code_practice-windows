import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["FangSong"]
plt.rcParams["axes.unicode_minus"] = False
plt.style.use("ggplot")

# 假设的市场份额数据
companies = ['亚马逊', '阿里巴巴', '京东', '拼多多', '其他']
market_shares = [37, 25, 12, 8, 18]  # 市场份额占比，这里只是示例数据

# 创建一个饼图
fig, ax = plt.subplots()
ax.pie(market_shares, labels=companies, autopct='%1.1f%%', startangle=90)

# 保证饼图是圆的
ax.axis('equal')

# 移除X轴和Y轴的标签
plt.axis('off')

# 显示图表
plt.show()
