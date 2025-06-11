def read_matrix(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    n = int(lines[0])
    A = [list(map(float, line.strip().split())) for line in lines[1:n+1]]
    return A

def transpose(M):
    return [list(row) for row in zip(*M)]

def matmul(A, B):
    return [[sum(a * b for a, b in zip(row, col)) for col in zip(*B)] for row in A]

def identity(n):
    return [[float(i == j) for j in range(n)] for i in range(n)]

def norm_squared(v):
    return sum(x**2 for x in v)

def householder_reflection(a):
    n = len(a)
    e1 = [1.0] + [0.0] * (n - 1)
    sign = 1 if a[0] >= 0 else -1
    norm_a = norm_squared(a) ** 0.5
    v = [a[i] + sign * norm_a * e1[i] for i in range(n)]
    v_norm_sq = norm_squared(v)
    return v, v_norm_sq

def construct_H(v, v_norm_sq, n, k):
    H = identity(n)
    for i in range(k, n):
        for j in range(k, n):
            H[i][j] -= 2 * v[i - k] * v[j - k] / v_norm_sq
    return H

def qr_decomposition(A):
    n = len(A)
    R = [row[:] for row in A]
    Q = identity(n)
    for k in range(n):
        x = [R[i][k] for i in range(k, n)]
        v, v_norm_sq = householder_reflection(x)
        H_k = construct_H(v, v_norm_sq, n, k)
        R = matmul(H_k, R)
        Q = matmul(Q, transpose(H_k))  # Q = H1ᵗ * H2ᵗ * ... * Hnᵗ
    return Q, R

def print_matrix(M, name):
    print(f"\n{name} =")
    for row in M:
        print("  ", " ".join(f"{x:.10f}" for x in row))

def max_off_diagonal_change(old_diag, new_diag):
    return max(abs(old_diag[i] - new_diag[i]) for i in range(len(old_diag)))

def qr_find_eigenvalues(A, eps=0.01, max_iter=1000):
    n = len(A)
    Ak = [row[:] for row in A]
    iter_count = 0
    while iter_count < max_iter:
        Q, R = qr_decomposition(Ak)
        Ak_next = matmul(R, Q)
        old_diag = [Ak[i][i] for i in range(n)]
        new_diag = [Ak_next[i][i] for i in range(n)]
        if max_off_diagonal_change(old_diag, new_diag) < eps:
            break
        Ak = Ak_next
        iter_count += 1
    print(f"\nИтераций: {iter_count}")
    return [Ak[i][i] for i in range(n)]

# === Основной запуск ===
A = read_matrix('input1_5.txt')
Q, R = qr_decomposition(A)
print_matrix(Q, "Q")
print_matrix(R, "R")
QR = matmul(Q, R)
print_matrix(QR, "Q * R (проверка)")

eigenvalues = qr_find_eigenvalues(A, eps=0.01)
print("\nСобственные значения:")
for val in eigenvalues:
    print(val)

