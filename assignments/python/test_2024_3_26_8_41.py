import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.colors import ListedColormap

# 定义细胞状态
DEAD = 0
ALIVE = 255
colors = ("purple", "yellow")
cmap = ListedColormap(colors)


# 定义滑翔机模式
def add_glider(i, j, grid):
    glider = np.array([[DEAD, DEAD, ALIVE], [ALIVE, DEAD, ALIVE],
                       [DEAD, ALIVE, ALIVE]])
    grid[i:i + 3, j:j + 3] = glider


# 随机生成初始细胞状态
def random_grid(size):
    return np.random.choice([DEAD, ALIVE], size * size,
                            p=[0.8, 0.2]).reshape(size, size)


# 更新细胞状态
def update(frame_num, image, grid, size):
    new_grid = grid.copy()
    for i in range(size):
        for j in range(size):
            total = int((grid[(i - 1) % size,
                              (j - 1) % size] + grid[(i - 1) % size, j] +
                         grid[(i - 1) % size,
                              (j + 1) % size] + grid[i, (j - 1) % size] +
                         grid[i, (j + 1) % size] + grid[(i + 1) % size,
                                                        (j - 1) % size] +
                         grid[(i + 1) % size, j] + grid[(i + 1) % size,
                                                        (j + 1) % size]) / 255)

            if grid[i, j] == ALIVE:
                if total < 2 or total > 3:
                    new_grid[i, j] = DEAD
            else:
                if total == 3:
                    new_grid[i, j] = ALIVE

    image.set_data(new_grid)
    grid[:] = new_grid[:]
    return image


def main(void):
    # 设置初始参数
    grid_size = 200
    update_interval = 50

    # 初始化细胞状态
    grid = random_grid(grid_size)
    add_glider(3, 3, grid)

    fig, ax = plt.subplots(facecolor="pink")
    image = ax.imshow(grid, cmap=cmap, interpolation="nearest")

    # 创建动画
    ani = animation.FuncAnimation(
        fig,
        update,
        fargs=(image, grid, grid_size),
        frames=None,  # 若要无限运行，请移除此行或设置为一个较大的数值
        interval=update_interval,
        save_count=50,
    )

    plt.show()


if __name__ == "__main__":
    main()
