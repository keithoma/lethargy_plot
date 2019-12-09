import numpy as np
from scipy import linalg


e = 2 * 10 ** (-16) # epsilon

A = [
    [e, -2 * e, 3],
    [4, -8, 6],
    [7, 8, 9]
]

B = [
    [e, -2, 3],
    [4, -8, 6],
    [7, 8, 9]
]

C = [
    [e, -2 * e, 3 * e],
    [4, -8, 6],
    [7, 8, 9]
]

b_1 = [3 - e, 2, 24]

b_2 = [1 + e, 2, 24]

b_3 = [2 * e, 2, 24]

def swap_row(mat, current_row):
    maximum = 0
    for i in range(current_row, len(mat)):
        for j in range(current_row, len(mat)):
            if abs(mat[j][i]) > maximum:
                maximum = abs(mat[i][j])
                index = i
    
    mat[index], mat[current_row] = mat[current_row], mat[index]
    return mat

def scale_row(row, b_entry):
    maximum = 0
    for value in row:
        if abs(value) > maximum:
            maximum = abs(value)

    if maximum != 0:
        row, b_entry = [entry / maximum for entry in row], b_entry / maximum
    return row, b_entry

def lu_decomposition(a, b, modified=True):
    n = len(a)
    if modified:
        for i in range(0, n):
            a[i], b[i] = scale_row(a[i], b[i])

    for i in range(n - 1):
        if modified:
            a = swap_row(a, i)

        for k in range(i + 1, n):
            l_ki = a[k][i] / a[i][i]

            a[k][i] = l_ki

            for j in range(i + 1, n):
                a[k][j] = a[k][j] - l_ki * a[i][j]

            b[k] = b[k] - l_ki * b[i]

    print(np.array(a))

    x = b
    for i in reversed(range(n)):
        for k in range(i + 1, n):
            x[i] = x[i] - a[i][k] * x[k]

        x[i] = x[i] / a[i][i]
    
    return x

exmp_B = [
    [5, 6, 6, 8],
    [2, 2, 2, 8],
    [6, 6, 2, 8],
    [2, 3, 6, 7]
]

c = [1, 2, 3, 4]

exmp_A = [
    [1, 2],
    [4, 3]
]

b = [4, 5]

lu_decomposition(exmp_A, b)