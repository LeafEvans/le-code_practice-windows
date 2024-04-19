import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

plt.rcParams["font.sans-serif"] = ["FangSong"]
plt.rcParams["axes.unicode_minus"] = False

ROWS = 100
COLS = 100

initial_tree_coverage_prob = 0.8
ignition_prob = 0.8
growth_prob = 0.001
lightning_ignition_prob = 0.00006

forest = (np.random.rand(ROWS, COLS) < initial_tree_coverage_prob).astype(np.int8)

fig = plt.figure()
plt.title("Step = 1")
colors = ["black", "lime", "red"]
bounds = [0, 1, 2, 3]
cmap = plt.matplotlib.colors.ListedColormap(colors)
image = plt.imshow(
    forest,
    cmap=cmap,
    norm=plt.matplotlib.colors.BoundaryNorm(bounds, cmap.N),
    interpolation="nearest",
)


def update(frame_num, image, forest):
    temp_forest = forest.copy()
    temp_forest[forest == 2] = 0

    p0 = np.random.rand(ROWS, COLS)
    temp_forest[(forest == 0) & (p0 < growth_prob)] = 1

    fire = (forest == 2).astype(np.int8)
    firepad = np.pad(
        fire,
        ((1, 1), (1, 1)),
        "wrap",
    )
    numfire = (
        firepad[0:-2, 1:-1]
        + firepad[2:, 1:-1]
        + firepad[1:-1, 0:-2]
        + firepad[1:-1, 2:]
    )

    p21 = np.random.rand(ROWS, COLS)
    p22 = np.random.rand(ROWS, COLS)
    temp_forest = np.where(
        (forest == 1)
        & (
            ((numfire == 0) & (p21 < lightning_ignition_prob))
            | ((numfire > 0) & (p22 < ignition_prob))
        ),
        2,
        temp_forest,
    )

    forest[:] = temp_forest[:]
    image.set_data(temp_forest)
    plt.title(
        "Step = " + str(frame_num),
    )
    return image


update_interval = 50

animation = animation.FuncAnimation(
    fig,
    update,
    fargs=(image, forest),
    frames=500,
    interval=update_interval,
    save_count=50,
)

plt.show()
