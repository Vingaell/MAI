import math
import matplotlib.pyplot as plt

# Точное решение
def y_exact(x):
    return x * math.sin(x) + math.cos(x)

# Правая часть: y'' = 2cos(x) - y
def f(x, y, y1):
    return y1

def g(x, y, y1):
    return 2 * math.cos(x) - y

# Метод Эйлера
def euler_method(x0, xn, h, y0, y1_0):
    X = []
    Y = []
    x = x0
    y = y0
    y1 = y1_0
    while x <= xn + 1e-10:
        X.append(x)
        Y.append(y)
        y1_new = y1 + h * g(x, y, y1)
        y_new = y + h * f(x, y, y1)
        y = y_new
        y1 = y1_new
        x += h
    return X, Y

# Метод Рунге-Кутты 4-го порядка
def runge_kutta_method(x0, xn, h, y0, y1_0):
    X = []
    Y = []
    x = x0
    y = y0
    y1 = y1_0
    while x <= xn + 1e-10:
        X.append(x)
        Y.append(y)

        K1 = h * f(x, y, y1)
        L1 = h * g(x, y, y1)

        K2 = h * f(x + h/2, y + K1/2, y1 + L1/2)
        L2 = h * g(x + h/2, y + K1/2, y1 + L1/2)

        K3 = h * f(x + h/2, y + K2/2, y1 + L2/2)
        L3 = h * g(x + h/2, y + K2/2, y1 + L2/2)

        K4 = h * f(x + h, y + K3, y1 + L3)
        L4 = h * g(x + h, y + K3, y1 + L3)

        y += (K1 + 2*K2 + 2*K3 + K4) / 6
        y1 += (L1 + 2*L2 + 2*L3 + L4) / 6
        x += h

    return X, Y

# Метод Адамса 4-го порядка (предиктор-корректор)
def adams_method(x0, xn, h, y0, y1_0):
    X = []
    Y = []

    # Сначала получим первые 4 точки методом Рунге-Кутты
    x = x0
    y = y0
    y1 = y1_0
    x_vals = [x]
    y_vals = [y]
    y1_vals = [y1]

    for _ in range(3):  # нужно 3 дополнительных шага
        K1 = h * f(x, y, y1)
        L1 = h * g(x, y, y1)

        K2 = h * f(x + h/2, y + K1/2, y1 + L1/2)
        L2 = h * g(x + h/2, y + K1/2, y1 + L1/2)

        K3 = h * f(x + h/2, y + K2/2, y1 + L2/2)
        L3 = h * g(x + h/2, y + K2/2, y1 + L2/2)

        K4 = h * f(x + h, y + K3, y1 + L3)
        L4 = h * g(x + h, y + K3, y1 + L3)

        y += (K1 + 2*K2 + 2*K3 + K4) / 6
        y1 += (L1 + 2*L2 + 2*L3 + L4) / 6
        x += h

        x_vals.append(x)
        y_vals.append(y)
        y1_vals.append(y1)

    X.extend(x_vals)
    Y.extend(y_vals)

    # Применяем формулы Адамса
    while x + h <= xn + 1e-10:
        f_vals = [f(x_vals[i], y_vals[i], y1_vals[i]) for i in range(-1, -5, -1)]
        g_vals = [g(x_vals[i], y_vals[i], y1_vals[i]) for i in range(-1, -5, -1)]

        y_next = y_vals[-1] + h / 24 * (55 * f_vals[0] - 59 * f_vals[1] + 37 * f_vals[2] - 9 * f_vals[3])
        y1_next = y1_vals[-1] + h / 24 * (55 * g_vals[0] - 59 * g_vals[1] + 37 * g_vals[2] - 9 * g_vals[3])

        x += h
        x_vals.append(x)
        y_vals.append(y_next)
        y1_vals.append(y1_next)

        X.append(x)
        Y.append(y_next)

    return X, Y

# Построение графиков и вывод ошибок
def plot_solutions(method_name, X, Y, X2, Y2, order):
    Y2_interp = [Y2[i * 2] for i in range(len(Y))]
    abs_errors = [abs(y_exact(X[i]) - Y[i]) for i in range(len(X))]
    abs_error_max = max(abs_errors)
    rr_errors = [abs(Y2_interp[i] - Y[i]) / (2 ** order - 1) for i in range(len(Y))]
    rr_error_max = max(rr_errors)

    plt.figure(figsize=(10, 6))
    plt.plot(X, [y_exact(x) for x in X], label='Точное решение', linewidth=2)
    plt.plot(X, Y, label=f'{method_name}', linestyle='--', marker='o')
    plt.plot(X, Y2_interp, label=f'{method_name} (Рунге-Ромберг)', linestyle='--', marker='x')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title(f'Сравнение решений ОДУ ({method_name})')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

    print(f"{method_name}:")
    print("Абсолютная погрешность:", abs_error_max)
    print("Погрешность (Рунге-Ромберг):", rr_error_max)

# Параметры
x0 = 0
xn = 1
h = 0.1
y0 = 1
y1_0 = 0

# Метод Эйлера
X_euler, Y_euler = euler_method(x0, xn, h, y0, y1_0)
_, Y_euler_h2 = euler_method(x0, xn, h / 2, y0, y1_0)
plot_solutions("Метод Эйлера", X_euler, Y_euler, _, Y_euler_h2, order=1)

# Метод Рунге-Кутты
X_rk, Y_rk = runge_kutta_method(x0, xn, h, y0, y1_0)
_, Y_rk_h2 = runge_kutta_method(x0, xn, h / 2, y0, y1_0)
plot_solutions("Метод Рунге-Кутты 4-го порядка", X_rk, Y_rk, _, Y_rk_h2, order=4)

# Метод Адамса 4-го порядка
X_adams, Y_adams = adams_method(x0, xn, h, y0, y1_0)
_, Y_adams_h2 = adams_method(x0, xn, h / 2, y0, y1_0)
plot_solutions("Метод Адамса 4-го порядка", X_adams, Y_adams, _, Y_adams_h2, order=4)