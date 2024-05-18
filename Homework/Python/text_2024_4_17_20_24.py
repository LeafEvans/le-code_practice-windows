import numpy as np
import pandas as pd
import cvxpy as cp

c = np.array([160, 130, 220, 170, 140, 130, 190, 150, 190, 200, 230])

left = np.array(
    [
        [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0],
        [0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0],
        [0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1],
        [0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0],
    ]
)

right_min = np.array([30, 70, 10, 10])
right_max = np.array([80, 140, 30, 50])
x = cp.Variable(11)
obj = cp.Minimize(c @ x)
con = [
    x >= 0,
    left @ x <= right_max,
    left @ x >= right_min,
    cp.sum(x[0:4]) == 50,
    cp.sum(x[4:8]) == 60,
    cp.sum(x[8:11]) == 50,
]

prob = cp.Problem(obj, con)
prob.solve(solver="COPT")
print(f"最优结果：{prob.value}")
print(f"参数取值：{x.value}")
