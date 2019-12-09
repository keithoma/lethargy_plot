import numpy as np

A_simpl = [
    [0, -3, -2],
    [1, -4, -2],
    [-3, 4, 1]
]

b_simpl = [1, 2, 3]

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

def gaus(A, b, modified=True):
    """ What we've learned:
    a) We need to swap the rows of the matrix to avoide zero-division-error.
    b) However, if we just swap the rows by searching for the largest entry, we might encounter another
       zero-division-errror, hence we scale the matrix.

    There is still an issue to be solved. If the very first entry of the matrix is 0, then we get a zero-
    division-error.

    Args:
        A (list): Must not be np.array.
        b (list): Must not be np.array.
    
    Returns:
        (list): The solution x to the equation Ax = b.
    """
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

    # We first scale the matrix, such that each row has 1 as its largest entry.
    if modified:
        A, b = scale_matrix(A, b)

    # Initializing L.
    L = [[1 if i == j else 0 for i in range(len(A))] for j in range(len(A))]

    # Create L and U via the Gaus algorithm.
    for i in range(len(A) - 1):
        # Swap rows necessary to avoide 0 division error.
        if modified:
            A, b = swap_row(A, b, i)


        for j in range(i + 1, len(A)):
            l_fac = A[j][i] / A[i][i]
            L[j][i] = l_fac

            A[j] = [bot - top * l_fac for bot, top in zip(A[j], A[i])]
            b[j] = b[j] - b[i] * l_fac

    # From here, A is the upper triangular matrix U.

    # Solve Ly = b for y, then solve Ux = b.
    y, x = [0 for _ in range(len(A))], [0 for _ in range(len(A))] # initializing

    for i in range(len(A)):
        y[i] = b[i]
        for j in range(i):
            y[i] = y[i] - b[j] * L[i][j]

    for i in reversed(range(len(A))):
        x[i] = y[i]
        for j in range(i + 1, len(A)):
            x[i] = x[i] - x[j] * A[i][j]
        x[i] = x[i] / A[i][i]

    return x

x_1 = gaus(A, b_1, False)
# x_2 = gaus(A, b_2, False)
# x_3 = gaus(A, b_3, False)

# print(np.array(x_1))
# print(np.array(x_2))
# print(np.array(x_3))
