import matplotlib.pyplot as plt
import random

plt.rc("font", family="Alibaba PuHuiTi 3.0", weight="bold", size=16)
# 还有可选的 weight 和 size 参数可选，前者是粗体等,后者是大小
plt.rc("axes", unicode_minus=False)

x = range(0, 120)
y = [random.randint(20, 35) for _ in range(120)]
plt.figure(figsize=(20, 8), dpi=80)
plt.plot(x, y)
_x = list(x)
# 调整 x 轴的刻度
_xtick_labels = [f"10点{_}分" for _ in range(60)]
_xtick_labels += [f"11点{_}分" for _ in range(60)]
# 取步长，数字和字符串一一对应，数据的长度一样
# 当又指定了一个新的参数，原本的 _x 就会变成 _xtick_labels 对应的映射
plt.xticks(_x[::3], _xtick_labels[::3], rotation=90)  # rotation 旋转的度数

# 添加描述信息
plt.xlabel("时间")
plt.ylabel("温度 单位（℃）")
plt.title("10点到12点每分钟的气温变化情况")
plt.show()
