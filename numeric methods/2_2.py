import matplotlib.pyplot as plt
import math

# Уравнения
def f1(x, y):
    return (x**2 + 9) * y - 27

def f2(x, y):
    return (x - 1.5)**2 + (y - 1.5)**2 - 9

# Частные производные
def df1_dx(x, y):
    return 2 * x * y

def df1_dy(x, y):
    return x**2 + 9

def df2_dx(x, y):
    return 2 * (x - 1.5)

def df2_dy(x, y):
    return 2 * (y - 1.5)

# Решение системы 2x2 линейных уравнений
def solve_linear_2x2(a11, a12, a21, a22, b1, b2):
    det = a11 * a22 - a12 * a21
    if abs(det) < 1e-12:
        return None, "Якобиан вырожден (определитель близок к нулю)"
    dx = b1 * a22 - b2 * a12
    dy = a11 * b2 - a21 * b1
    return dx / det, dy / det

# Метод Ньютона
def newton_system(x0, y0, epsilon=1e-5, max_iter=100):
    iterations = 0
    while iterations < max_iter:
        f1_val = f1(x0, y0)
        f2_val = f2(x0, y0)

        a11 = df1_dx(x0, y0)
        a12 = df1_dy(x0, y0)
        a21 = df2_dx(x0, y0)
        a22 = df2_dy(x0, y0)

        result = solve_linear_2x2(a11, a12, a21, a22, -f1_val, -f2_val)
        if result is None or isinstance(result, str):
            return None, iterations, result

        dx, dy = result
        x1 = x0 + dx
        y1 = y0 + dy

        if abs(dx) < epsilon and abs(dy) < epsilon:
            return (x1, y1), iterations + 1, None

        x0, y0 = x1, y1
        iterations += 1

    return (x0, y0), iterations, None

def phi_y(x):
    return 27 / (x ** 2 + 9)

def phi_x(y, switch):
    radicand = 9 - (y - 1.5) ** 2
    if radicand < 0:
        return None
    return 1.5 + switch * math.sqrt(radicand)

# Частные производные φ-функций для оценки сходимости
def dphi_y_dx(x):
    return -54 * x / (x**2 + 9)**2

def dphi_x_dy(y, switch):
    radicand = 9 - (y - 1.5)**2
    if radicand <= 0:
        return None
    return switch * (y - 1.5) / math.sqrt(radicand)

def check_convergence_condition(x0, y0, switch):
    try:
        dphi_y = abs(dphi_y_dx(x0))
        dphi_x = abs(dphi_x_dy(y0, switch))
        if dphi_x is None:
            return None 
        norm = max(dphi_x, dphi_y)
        return norm < 1
    except:
        return None

def simple_iterations(x0, y0, epsilon, switch=1, max_iter=100):
    x, y = x0, y0
    for iteration in range(1, max_iter + 1):
        y_new = phi_y(x)
        x_new = phi_x(y_new, switch)

        if x_new is None:
            return None, iteration, "Выход за область определения φ-функции"

        if abs(x_new - x) < epsilon and abs(y_new - y) < epsilon:
            return (x_new, y_new), iteration, None

        x, y = x_new, y_new

    return (x, y), max_iter, "Превышено число итераций"

def draw_graph():
    x_vals = [i * 0.05 for i in range(-100, 101)]
    y_vals = [i * 0.05 for i in range(-100, 101)]

    X = [[x for x in x_vals] for _ in y_vals]
    Y = [[y for _ in x_vals] for y in y_vals]

    Z1 = [[f1(x, y) for x in x_vals] for y in y_vals]
    Z2 = [[f2(x, y) for x in x_vals] for y in y_vals]

    plt.figure(figsize=(8, 6))
    plt.contour(x_vals, y_vals, Z1, levels=[0], colors='red', linewidths=2)
    plt.contour(x_vals, y_vals, Z2, levels=[0], colors='blue', linewidths=2)
    plt.axhline(0, color='red', linewidth=0.5)
    plt.axvline(0, color='blue', linewidth=0.5)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.grid(True)
    plt.title("Графики уравнений")
    plt.legend(["(x²+9)y−27 = 0", "(x−1.5)²+(y−1.5)²−9 = 0"])
    plt.show()

if __name__ == "__main__":
    draw_graph()  

    try:
        x0_str, y0_str = input("Введите начальные приближения x0 и y0: ").split()
        x0, y0 = float(x0_str), float(y0_str)
        epsilon = float(input("Введите точность ε: "))

        # Метод Ньютона
        print("\n[Метод Ньютона]")
        result_newton, iterations_newton, error_newton = newton_system(x0, y0, epsilon)
        if error_newton:
            print(f"Ошибка: {error_newton}")
        else:
            print(f"Решение найдено за {iterations_newton} итераций:")
            print(f"x = {result_newton[0]}")
            print(f"y = {result_newton[1]}")
            print(f"Проверка: f1 = {f1(result_newton[0], result_newton[1])}, f2 = {f2(result_newton[0], result_newton[1])}")

        # Метод простых итераций
        print("\n[Метод простых итераций]")

        # Определяем, какую φ-функцию использовать
        switch = -1 if x0 < 0 else 1

        # Проверка достаточного условия сходимости 
        conv = check_convergence_condition(x0, y0, switch)
        if conv is None:
            print("Предупреждение: невозможно вычислить норму φ' в точке — вне области определения.")
        elif not conv:
            print("Предупреждение: достаточное условие сходимости ||φ'(x₀)|| < 1 не выполнено.")
        else:
            print("OK: достаточное условие сходимости выполнено (||φ'(x₀)|| < 1).")

        result_iter, iterations_iter, error_iter = simple_iterations(x0, y0, epsilon, switch)
        if error_iter:
            print(f"Ошибка: {error_iter}")
        else:
            print(f"Решение найдено за {iterations_iter} итераций:")
            print(f"x = {result_iter[0]}")
            print(f"y = {result_iter[1]}")
            print(f"Проверка: f1 = {f1(result_iter[0], result_iter[1])}, f2 = {f2(result_iter[0], result_iter[1])}")

    except Exception as e:
        print(f"\nОшибка: {e}")


