import sympy as sp
from scipy.integrate import odeint, quad, dblquad, solve_ivp
from scipy.optimize import fsolve, root
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["FangSong"]
plt.rcParams["axes.unicode_minus"] = False
plt.style.use("ggplot")


def func(point, t, args):
    p, r, b = args
    x, y, z = point
    return np.array([p * (y - x), x * (r - z), x * y - b * z])


t = np.arange(0, 30, 0.001)
p1 = odeint(func, (0.0, 1.0, 0.0), t, args=([10.0, 28.0, 3.0], ))
p2 = odeint(func, (0.0, 1.01, 0.0), t, args=([10.0, 28.0, 3.0], ))

fig = plt.figure()
ax = fig.add_subplot(projection="3d")
ax.plot(p1[:, 0], p1[:, 1], p1[:, 2])
ax.plot(p2[:, 0], p2[:, 1], p2[:, 2])
plt.show()
