import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.colors import ListedColormap

plt.rcParams["font.sans-serif"] = ["FangSong"]
plt.rcParams["axes.unicode_minus"] = False

DEAD = 0
ALIVE = 255
colors = ("purple", "yellow")
cmap = ListedColormap(colors)


def addGlider(i, j, grid):
    glider = np.array([[DEAD, DEAD, ALIVE], [ALIVE, DEAD, ALIVE], [DEAD, ALIVE, ALIVE]])
    grid[i : i + 3, j : j + 3] = glider


def randomGrid(size):
    return np.random.choice([DEAD, ALIVE], size * size, p=([0.8, 0.2])).reshape(
        size, size
    )


def updata(frame_num, image, grid, size):
    new_grid = grid.copy()
    for i in range(size):
        for j in range(size):
            total = int(
                (
                    grid[(i - 1) % size, (j - 1) % size]
                    + grid[(i - 1) % size, j]
                    + grid[(i - 1) % size, (j + 1) % size]
                    + grid[i, (j - 1) % size]
                    + grid[i, (j + 1) % size]
                    + grid[(i + 1) % size, (j - 1) % size]
                    + grid[(i + 1) % size, j]
                    + grid[(i + 1) % size, (j + 1) % size]
                )
                / 255
            )

            if grid[i, j] == ALIVE:
                if total < 2 or total > 3:
                    new_grid[i, j] = DEAD
            else:
                if total == 3:
                    new_grid[i, j] = ALIVE

    image.set_data(new_grid)
    grid[:] = new_grid[:]
    return image


grid_size = 200
updata_interval = 50

grid = randomGrid(grid_size)
addGlider(3, 3, grid)
fig, ax = plt.subplots(facecolor="pink")
image = ax.imshow(grid, cmap=cmap, interpolation="nearest")

animation = animation.FuncAnimation(
    fig,
    updata,
    fargs=(image, grid, grid_size),
    frames=None,
    interval=updata_interval,
    save_count=50,
)
plt.show()
