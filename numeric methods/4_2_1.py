import math
import sys
import matplotlib.pyplot as plt

def f(x, y1, y2):
    return (x * y1 - 2 * y2) / x

def runge_kutta_step(x, y1, y2, h):
    k1_y1 = y2
    k1_y2 = f(x, y1, y2)

    k2_y1 = y2 + 0.5 * h * k1_y2
    k2_y2 = f(x + 0.5 * h, y1 + 0.5 * h * k1_y1, y2 + 0.5 * h * k1_y2)

    k3_y1 = y2 + 0.5 * h * k2_y2
    k3_y2 = f(x + 0.5 * h, y1 + 0.5 * h * k2_y1, y2 + 0.5 * h * k2_y2)

    k4_y1 = y2 + h * k3_y2
    k4_y2 = f(x + h, y1 + h * k3_y1, y2 + h * k3_y2)

    y1_next = y1 + (h / 6.0) * (k1_y1 + 2*k2_y1 + 2*k3_y1 + k4_y1)
    y2_next = y2 + (h / 6.0) * (k1_y2 + 2*k2_y2 + 2*k3_y2 + k4_y2)

    return y1_next, y2_next

def solve_ode(s, h=0.01):
    x = 1.0
    y1 = math.exp(-1)
    y2 = s

    xs = [x]
    ys = [y1]

    while x < 2.0:
        y1, y2 = runge_kutta_step(x, y1, y2, h)
        x += h
        xs.append(x)
        ys.append(y1)
    return xs, ys

def F(s, h=0.01):
    xs, ys = solve_ode(s, h)
    y_val = ys[-1]
    return y_val - 0.5 * math.exp(-2)

def shooting_method(s0, s1, eps=1e-6, max_iter=100, h=0.01):
    F0 = F(s0, h)
    F1 = F(s1, h)

    if F0 * F1 > 0:
        print("Значения функции F(s) на начальных приближениях не имеют разных знаков.")
        print("Метод стрельбы не применим. Завершение программы.")
        sys.exit(1)

    s_values = [s0, s1]
    solutions = []

    xs0, ys0 = solve_ode(s0, h)
    xs1, ys1 = solve_ode(s1, h)
    solutions.append((xs0, ys0))
    solutions.append((xs1, ys1))

    for i in range(2, max_iter+2):
        if abs(F1) < eps:
            return s1, s_values, solutions
        denominator = F1 - F0
        if abs(denominator) < 1e-15:
            break
        s2 = s1 - F1 * (s1 - s0) / denominator
        F2 = F(s2, h)

        s_values.append(s2)
        xs2, ys2 = solve_ode(s2, h)
        solutions.append((xs2, ys2))

        s0, s1 = s1, s2
        F0, F1 = F1, F2

    print("Метод не сошёлся за заданное число итераций.")
    sys.exit(1)

def exact_solution(x):
    return math.exp(-x) / x

def runge_romberg(y_h, y_h2, h, p=4):
    error = 0.0
    n = min(len(y_h), len(y_h2) // 2)
    for i in range(n):
        err_i = abs(y_h[i] - y_h2[2*i]) / (2**p - 1)
        if err_i > error:
            error = err_i
    return error

def plot_additional_solutions(s_list, h=0.01):
    for s in s_list:
        xs, ys = solve_ode(s, h)
        plt.plot(xs, ys, linestyle=':', alpha=0.7)

# Запуск метода
s0 = -1.0
s1 = 0.0
h = 0.01

s_found, s_values, solutions = shooting_method(s0, s1, eps=1e-6, max_iter=100, h=h)

xs, ys = solve_ode(s_found, h)
h2 = h / 2
xs2, ys2 = solve_ode(s_found, h2)
error_rr = runge_romberg(ys, ys2, h)
print(f"Ошибка Рунге-Ромберга (приближённая) = {error_rr}")

plt.figure(figsize=(10,6))

# Веер решений метода стрельбы — просто пронумеруем по порядку без s в подписи
for idx, (xs_sol, ys_sol) in enumerate(solutions, 1):
    plt.plot(xs_sol, ys_sol, label=f"S{idx}", alpha=0.6)

# Дополнительные s
additional_s = [s_found - 0.2, s_found - 0.1, s_found, s_found + 0.1, s_found + 0.2]
plot_additional_solutions(additional_s, h=h)

# Точное решение
x_exact = [1 + i * 0.001 for i in range(1001)]
y_exact = [exact_solution(x) for x in x_exact]
plt.plot(x_exact, y_exact, 'k--', linewidth=2, label="Точное решение")

plt.xlabel("x")
plt.ylabel("y")
plt.title("Веер решений метода стрельбы")
plt.legend(fontsize=9)
plt.grid(True)
plt.tight_layout()
plt.show()
