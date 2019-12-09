#! /usr/bin/env python3

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

def solve(a, b, modified=True):

    def swap_row(A, b, current_row):
        maximum = 0
        for i in range(current_row, len(A)):
            for j in range(current_row, len(A)):
                if abs(A[i][j]) > maximum:
                    maximum = abs(A[i][j])
                    index = i

        A[index], A[current_row] = A[current_row], A[index]
        b[index], b[current_row] = b[current_row], b[index]
        return A, b

    def scale_matrix(A, b):
        for i in range(len(A)):
            maximum = 0
            for value in A[i]:
                if abs(value) > maximum:
                    maximum = abs(value)

            if maximum != 0:
                A[i], b[i] = [entry / maximum for entry in A[i]], b[i] / maximum
        return A, b

    n = len(a)

    if modified:
        a, b = scale_matrix(a, b)

    for i in range(n - 1):
        if modified:
            a, b = swap_row(a, b, i)

        for k in range(i + 1, n):
            l_ki = a[k][i] / a[i][i]

            a[k][i] = l_ki

            for j in range(i + 1, n):
                a[k][j] = a[k][j] - l_ki * a[i][j]
            
            b[k] = b[k] - l_ki * b[i]
        
    x = b
    for i in reversed(range(n)):
        for k in range(i + 1, n):
            x[i] = x[i] - a[i][k] * x[k]
        x[i] = x[i] / a[i][i]
    return x

# print(solve(A, b_1, False))
# print(solve(B, b_2, False))
print(solve(C, b_3, False))

# print(solve(A, b_1))
# print(solve(B, b_2))
# print(solve(C, b_3))