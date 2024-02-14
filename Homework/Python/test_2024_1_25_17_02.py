import matplotlib.pyplot as plt
import random
from matplotlib import font_manager

my_font = font_manager.FontProperties(
    fname="C:\\Users\\31866\\AppData\\Local\\Microsoft\\Windows\\Fonts\\苹方-简 中粗体.otf",
    size=12,
)
# 初始化一个实例
x = range(0, 120)
y = [random.randint(20, 35) for _ in range(120)]
plt.figure(figsize=(20, 8), dpi=80)
plt.plot(x, y)
_x = list(x)
_xtick_labels = [f"10点{_}分" for _ in range(60)]
_xtick_labels += [f"11点{_}分" for _ in range(60)]
plt.xticks(_x[::3], _xtick_labels[::3], rotation=45, fontproperties=my_font)
# 添加一个字体参数
plt.show()
