from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap, BoundaryNorm

# 设置森林地区的行和列
ROWS = 100
COLS = 100

# 初始化森林地区的参数
initial_tree_coverage_prob = 0.8  # 初始树木覆盖概率
ignition_prob = 0.8  # 绿树受到周围树木引燃的概率
growth_prob = 0.001  # 空地上长出树木的概率
lightning_ignition_prob = 0.00006  # 闪电引燃绿树的概率

# 创建森林地区的初始状态
forest = (np.random.rand(ROWS, COLS) < initial_tree_coverage_prob).astype(np.int8)

# 初始化作图
plt.title("Step = 1", fontdict={"family": "Inter", "weight": "bold", "fontsize": 20})
colors = ["black", "lime", "red"]  # 黑色空地 绿色树 红色火
bounds = [0, 1, 2, 3]  # 边界序列，用于指定颜色的分界点
cmap = ListedColormap(colors)  # 创建颜色映射对象
image = plt.imshow(forest, cmap=cmap, norm=BoundaryNorm(bounds, cmap.N))

# 迭代更新森林状态
NUM_ITERATIONS = 500  # 迭代次数
for t in range(NUM_ITERATIONS):
    temp_forest = forest.copy()

    # 更新森林地区的状态
    temp_forest = np.where(forest == 2, 0, temp_forest)
    p0 = np.random.rand(ROWS, COLS)
    temp_forest = np.where(
        (forest == 0) & (p0 < growth_prob), 1, temp_forest
    )  # 空地长出树木

    fire = (forest == 2).astype(np.int8)
    firepad = np.pad(
        fire,
        ((1, 1), (1, 1)),
        "wrap",
    )  # 上下边界，左右边界相连接
    numfire = (
        firepad[0:-2, 1:-1]  # 上方位置
        + firepad[2:, 1:-1]  # 下方位置
        + firepad[1:-1, 0:-2]  # 左侧位置
        + firepad[1:-1, 2:]  # 右侧位置
    )
    p21 = np.random.rand(ROWS, COLS)  # 绿树因为引燃而变成燃烧的树
    p22 = np.random.rand(ROWS, COLS)  # 绿树因为闪电而变成燃烧的树
    temp_forest = np.where(
        (forest == 1)
        & (
            ((numfire == 0) & (p21 < lightning_ignition_prob))
            | ((numfire > 0) & (p22 < ignition_prob))
        ),
        2,
        temp_forest,
    )

    forest = temp_forest  # 更新森林状态

    # 更新图像显示
    plt.title(
        "Step = " + str(t),
        fontdict={"family": "Inter", "weight": "bold", "fontsize": 20},
    )
    image.set_data(forest)
    plt.pause(0.1)
    plt.savefig(f"C:\\Users\\31866\\Pictures\\画图\\forest_fire_{t}.png")

# 生成 GIF 动画
images = [
    Image.open(f"C:\\Users\\31866\\Pictures\\画图\\forest_fire_{i}.png")
    for i in range(NUM_ITERATIONS)
]

images[0].save(
    "C:\\Users\\31866\\Pictures\\画图\\forest_fire.gif",
    save_all=True,
    append_images=images[1:],
    duration=100,
    loop=0,
)
