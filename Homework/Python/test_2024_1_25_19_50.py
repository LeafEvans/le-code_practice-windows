import matplotlib.pyplot as plt

plt.rc("font", family="LXGW WenKai",style="italic")


t = range(11, 31)
a = [1, 0, 1, 1, 2, 4, 3, 2, 3, 4, 4, 5, 6, 5, 4, 3, 3, 1, 1, 1]
b = [1, 0, 3, 1, 2, 2, 3, 3, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1]
plt.figure(figsize=(20, 8), dpi=100)
a_max_index, a_max = 11 + a.index(max(a)), max(a)
b_max_index, b_max = 11 + b.index(max(b)), max(b)
_xtick_labels = [f"{_}岁" for _ in t]
plt.xticks(t, _xtick_labels)

plt.plot(t, a, label="自己", color="orange")
plt.plot(t, b, label="同桌", color="m")
plt.annotate(
    "NB",
    xy=(a_max_index, a_max),
    xytext=(a_max_index + 3, a_max),
    color="yellow",
    arrowprops=dict(color="red", arrowstyle="-|>"),
)
plt.legend()
plt.yticks(range(0, 9))
plt.xlabel("年龄")
plt.ylabel("男（女）朋友数量")
plt.title("交男女朋友的数量趋势", fontsize=20)
# 绘制网格
plt.grid(axis="y")
# alpha 是透明度，由 0 到 1.

plt.show()
