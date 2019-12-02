# super fucking naive implementation because its late and I need it for home work ...

import numpy as np
from scipy import linalg

hilbert_six = np.array([
    [  1, 1/2, 1/3, 1/4,  1/5,  1/6],
    [1/2, 1/3, 1/4, 1/5,  1/6,  1/7],
    [1/3, 1/4, 1/5, 1/6,  1/7,  1/8],
    [1/4, 1/5, 1/6, 1/7,  1/8,  1/9],
    [1/5, 1/6, 1/7, 1/8,  1/9, 1/10],
    [1/6, 1/7, 1/8, 1/9, 1/10, 1/11]
])

# ----------

x_1 = np.array([1, 1, 1, 1, 1, 1])
b_1 = np.matmul(hilbert_six, x_1)

dx_1 = np.array([10 ** (-6), 0, 0, 0, 0, 0])
db_1 = np.matmul(hilbert_six, dx_1)

print(b_1)
print(db_1)
print("\n-----\n")

# ----------

x_2 = np.array([
    1.809482541440515 * 10 ** (-3),
    -5.161825359424858 * 10 ** (-2),
    3.489077525355039 * 10 ** (-1),
    -9.067176845784127 * 10 ** (-1), 
    1,
    -3.937411114937020 * 10 ** (-1)
])
b_2 = np.matmul(hilbert_six, x_2)

dx_2 = np.array([
    1,
    0.5886,
    0.4283,
    0.3397,
    0.2825,
    0.2423,
])
db_2 = np.matmul(hilbert_six, dx_2)

print(b_2)
print(db_2)