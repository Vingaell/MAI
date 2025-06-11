import math
import matplotlib.pyplot as plt

# Параметры задачи
a, b = 1.0, 2.0
ya = math.exp(-a)          # y(1) = e^{-1}
yb = 0.5 * math.exp(-b)    # y(2) = 0.5 e^{-2}

# Функции p(x), q(x), f(x)
def p(x): return 2 / x
def q(x): return -1
def f(x): return 0.0  # однородное уравнение

def solve_fdm(n):
    h = (b - a) / (n + 1)
    x = [a + (i+1)*h for i in range(n)]

    A = [[0.0]*n for _ in range(n)]
    d = [0.0]*n

    for i in range(n):
        xi = x[i]
        pi = p(xi)
        qi = q(xi)

        A[i][i] = h**2 * qi - 2
        if i > 0:
            A[i][i-1] = 1 - h * pi / 2
        if i < n - 1:
            A[i][i+1] = 1 + h * pi / 2

        d[i] = h**2 * f(xi)

    d[0]   -= (1 - h * p(x[0]) / 2) * ya
    d[-1] -= (1 + h * p(x[-1]) / 2) * yb

    def lu_decomposition(M):
        n = len(M)
        L = [[0.0]*n for _ in range(n)]
        U = [[0.0]*n for _ in range(n)]
        for i in range(n):
            L[i][i] = 1.0
        for j in range(n):
            for i in range(j+1):
                s = sum(U[k][j]*L[i][k] for k in range(i))
                U[i][j] = M[i][j] - s
            for i in range(j+1, n):
                s = sum(U[k][j]*L[i][k] for k in range(j))
                if abs(U[j][j]) < 1e-15:
                    raise ZeroDivisionError("LU decomposition failed: zero pivot")
                L[i][j] = (M[i][j] - s) / U[j][j]
        return L, U

    def forward_substitution(L, b):
        n = len(b)
        y = [0.0]*n
        for i in range(n):
            y[i] = b[i] - sum(L[i][j]*y[j] for j in range(i))
        return y

    def backward_substitution(U, y):
        n = len(y)
        x = [0.0]*n
        for i in reversed(range(n)):
            if abs(U[i][i]) < 1e-15:
                raise ZeroDivisionError("Back substitution failed: zero pivot")
            x[i] = (y[i] - sum(U[i][j]*x[j] for j in range(i+1, n))) / U[i][i]
        return x

    L, U = lu_decomposition(A)
    y_internal = backward_substitution(U, forward_substitution(L, d))

    x_full = [a] + x + [b]
    y_full = [ya] + y_internal + [yb]
    return x_full, y_full

# Основное решение с шагом h
n1 = 10
x1, y1 = solve_fdm(n1)

# Решение с шагом h/2
n2 = 2 * n1
_, y2 = solve_fdm(n2)

# Расчёт ошибки Рунге–Ромберга (только для внутренних точек)
p_order = 2
errors = []
for i in range(n1):
    y1_i = y1[i+1]
    y2_i = y2[2*i + 1]
    rr_error = abs(y1_i - y2_i) / (2**p_order - 1)
    errors.append(rr_error)

max_error = max(errors)
print(f"Ошибка Рунге–Ромберга: {max_error:.6e}")

# Точное решение
def exact_solution(x): return math.exp(-x) / x
x_exact = [a + i*0.01 for i in range(int((b - a)/0.01)+1)]
y_exact = [exact_solution(xi) for xi in x_exact]

# График
plt.plot(x_exact, y_exact, label="Точное решение", color="red")
plt.scatter(x1, y1, color="blue", label="Численное решение (n=10)", s=25)
plt.xlabel("x")
plt.ylabel("y")
plt.title("Конечно-разностный метод")
plt.legend()
plt.grid(True)
plt.show()
