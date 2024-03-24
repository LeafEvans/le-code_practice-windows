import numpy as np
import matplotlib.pyplot as plt

# 初始条件函数 U(x, 0)
def initial_condition(x, p):
    u0 = np.sin(2 * (x - p) ** 2)
    return u0

# 输入参数
velocity = 1.0  # 平流方程参数，系统速度
p = 0.25  # 初始条件函数 U(x, 0) 中的参数

# 时间参数
start_time = 0  # 开始时间
end_time = 1.0  # 终止时间：(0, end_time)
dt = 0.02  # 时间步长
n_nodes = 100  # 空间网格数

# 初始化
n_steps = round(end_time / dt)
dx = np.pi / n_nodes
x = np.arange(0, np.pi + 2 * dx, dx)
u_curr = initial_condition(x, p)
u_next = u_curr.copy()

# 时域差分
for _ in range(n_steps):
    plt.clf()  # 清除当前 figure 的所有 axes，但是保留当前窗口

    # 计算 u(j + 1)
    for i in range(1, n_nodes + 1):
        u_next[i] = u_curr[i] - (velocity * dt / dx) * (u_curr[i] - u_curr[i - 1])

    # 更新边界条件
    u_next[0] = u_next[n_nodes]
    u_next[n_nodes + 1] = u_next[1]
    u_curr = u_next.copy()

    # 更新时间
    start_time += dt

    # 绘图
    plt.plot(x, u_curr, "b-", label="Velocity = 1.0")
    plt.axis((0 - 0.1, np.pi + 0.1, -1.1, 1.1))
    plt.xlabel("x")
    plt.ylabel("U(x)")
    plt.legend(loc=(0.05, 0.05))
    plt.title(f"Advection equation with finite difference method, t = {start_time + dt:.1f}")
    plt.text(0.05, 0.9, "ypucans-xupt", color="gainsboro")
    plt.pause(0.001)

plt.show()
