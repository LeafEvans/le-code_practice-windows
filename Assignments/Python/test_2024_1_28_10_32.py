import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

def dmove(t, Point, p, r, b):
    x, y, z = Point
    return [p * (y - x), x * (r - z), x * y - b * z]

t = np.arange(0, 50, 0.001)

P1 = solve_ivp(dmove, y0=(0.0, 1.0, 0.0), t_eval=t, t_span=[0, 50], args=(10.0, 28.0, 3.0))
P2 = solve_ivp(dmove, y0=(0.0, 1.01, 0.0), t_eval=t, t_span=[0, 50], args=(10.0, 28.0, 3.0))

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")
ax.plot(P1.y[0], P1.y[1], P1.y[2])
ax.plot(P2.y[0], P2.y[1], P2.y[2])
plt.show()
