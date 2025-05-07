import numpy as np
import matplotlib.pyplot as plt

# 模型参数
c = 1.0  # 波的传播速度
tc, te = 0.0, 1.0  # 时间范围：(0, te)
xa, xb = 0.0, 1.0  # 空间范围：(xa, xb)
ya, yb = 0.0, 1.0  # 空间范围：(ya, yb)

# 初始化
c2 = c * c  # 方程参数
dt = 0.01  # 时间步长
dx = dy = 0.02  # 空间步长
t_nodes = round(te / dt)  # t轴 时序网格数
x_nodes = round((xb - xa) / dx)  # x轴 空间网格数
y_nodes = round((yb - ya) / dy)  # y轴 空间网格数
t_zone = np.arange(0, (t_nodes + 1) * dt, dt)  # 建立空间网格
x_zone = np.arange(0, (x_nodes + 1) * dx, dx)  # 建立空间网格
y_zone = np.arange(0, (y_nodes + 1) * dy, dy)  # 建立空间网格
xx, yy = np.meshgrid(x_zone, y_zone)  # 生成网格点的坐标 xx, yy （二维数组）

# 步长笔检验 (r > 1，则算法不稳定)
r = 4 * c2 * dt * dt / (dx * dx + dy * dy)
print("dt = {:.2f}, dx = {:.2f}, dy = {:.2f}, r = {:.2f}".format(
    dt, dx, dy, r))
assert r < 1.0, "Error: r > 1, unstable step ratio of dt2 / (dx2 + dy2)."
rx = c * c * dt**2 / dx**2
ry = c * c * dt**2 / dy**2

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection="3d")

# 计算初始值
U = np.zeros([t_nodes + 1, x_nodes + 1, y_nodes + 1])  # 建立三维数组
U[0] = np.sin(6 * np.pi * xx) + np.cos(4 * np.pi * yy)  # U[0, :, :]
U[1] = np.sin(6 * np.pi * xx) + np.cos(4 * np.pi * yy)  # U[1, :, :]
surf = ax.plot_surface(xx,
                       yy,
                       U[0, :, :],
                       rstride=2,
                       cstride=2,
                       cmap=plt.cm.coolwarm)

for k in range(2, t_nodes + 1):
    for i in range(1, x_nodes):
        for j in range(1, y_nodes):
            U[k, i, j] = (rx * (U[k - 1, i - 1, j] + U[k - 1, i + 1, j] + ry *
                                (U[k - 1, i, j - 1]) + U[k - 1, i, j + 1]) +
                          2 * (1 - rx - ry) * U[k - 1, i, j] - U[k - 2, i, j])
    surf = ax.plot_surface(xx,
                           yy,
                           U[k, :, :],
                           rstride=2,
                           cstride=2,
                           cmap="rainbow")
    ax.set_title(f"2D wave equation (t = {k * dt:.2f})")
    plt.pause(0.001)

plt.show()
