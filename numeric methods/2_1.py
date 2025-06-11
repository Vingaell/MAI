import math
import matplotlib.pyplot as plt

# Определение функции и её производной
def f(x):
    return math.log(x + 2) - x ** 2

def f_prime(x):
    return 1 / (x + 2) - 2 * x

def f_double_prime(x):
    return -1 / (x + 2) ** 2 - 2  # Вторая производная функции

# Проверка на разные знаки на концах отрезка
def check_signs(a, b):
    f_a = f(a)
    f_b = f(b)
    if f_a * f_b > 0:
        print("Значения функции на концах отрезка имеют одинаковый знак!")
        return False
    return True

# Проверка на f(x) * f''(x) > 0
def condition_1(x):
    return f(x) * f_double_prime(x) > 0

# Проверка на f(x) * f''(x) <= (f'(x))^2
def condition_2(x):
    return abs(f(x) * f_double_prime(x)) <= (f_prime(x)) ** 2

# Явно заданная функция φ(x) и её производная
def phi(x):
    return math.sqrt(math.log(x + 2))

def phi_prime(x):
    return 1 / (2 * math.sqrt(math.log(x + 2)) * (x + 2))


# Метод Ньютона
def newton_method(a, b, epsilon, max_iterations=100):
    if not check_signs(a, b):
        print("Значения функции на концах интервала имеют одинаковый знак.")
        return None, 0

    status = {a: {'cond1': False, 'cond2': False}, b: {'cond1': False, 'cond2': False}}

    # Проверка первого условия
    if condition_1(a):
        status[a]['cond1'] = True
    if condition_1(b):
        status[b]['cond1'] = True

    # Если ни одна точка не прошла первое условие
    if not status[a]['cond1'] and not status[b]['cond1']:
        print("Условие сходимости (1) не выполняется ни для a, ни для b.")
        return None, 0

    # Проверка второго условия для тех, кто прошёл первое
    candidates = []
    for x in [a, b]:
        if status[x]['cond1'] and condition_2(x):
            status[x]['cond2'] = True
            candidates.append(x)

    if not candidates:
        print("Условие сходимости (2) не выполняется для оставшихся после первой проверки точек.")
        return None, 0

    # Выбор начальной точки
    if len(candidates) == 2:
        x0 = min(candidates, key=lambda x: abs(f(x)))
    else:
        x0 = candidates[0]

    # Итерации метода Ньютона
    iterations = 0
    while iterations < max_iterations:
        fx = f(x0)
        fpx = f_prime(x0)

        if abs(fpx) < 1e-12:
            print(f"Производная в точке {x0} слишком мала (f'({x0}) = {fpx}), метод Ньютона может не сойтись.")
            return None, iterations

        x1 = x0 - fx / fpx

        if abs(x1 - x0) < epsilon:
            return x1, iterations + 1

        x0 = x1
        iterations += 1

    return x0, iterations



# Метод простых итераций
def simple_iterations_manual_phi(a, b, epsilon, max_iter=1000):
    # Проверка на разные знаки
    if not check_signs(a, b):
        return None, 0
    # Проверим условие сходимости |φ'(x)| < 1 на концах
    if abs(phi_prime(a)) >= 1 or abs(phi_prime(b)) >= 1:
        print("Условие сходимости |φ'(x)| < 1 не выполняется на концах отрезка.")
        return None, 0

    x0 = (a + b) / 2
    iterations = 0

    while iterations < max_iter:
        try:
            x1 = phi(x0)
        except ValueError:
            print(f"Ошибка вычисления φ({x0})")
            return None, iterations

        if abs(x1 - x0) < epsilon:
            return x1, iterations + 1

        x0 = x1
        iterations += 1

    return x0, iterations


# Построение графика функций
def plot_functions():
    x_values = []
    y1_values = []
    y2_values = []
    
    x = -1.9
    while x <= 2:
        x_values.append(x)
        y1_values.append(math.log(x + 2))
        y2_values.append(x ** 2)
        x += 0.01

    plt.plot(x_values, y1_values, label='ln(x + 2)', color='blue')
    plt.plot(x_values, y2_values, label='x²', color='red')
    plt.title('Графики функций ln(x + 2) и x²')
    plt.grid(True)
    plt.legend()
    plt.show()
    
# Анализ зависимости числа итераций от точности
def plot_iterations_vs_epsilon(a, b):
    epsilons = [10 ** (-i) for i in range(1, 15)]
    eps_labels = [f"1e-{i}" for i in range(1, 15)]
    
    iterations_newton = []
    iterations_simple = []

    for eps in epsilons:
        # Метод Ньютона
        _, iters_n = newton_method(a, b, eps)
        iterations_newton.append(iters_n)

        # Метод простых итераций
        _, iters_s = simple_iterations_manual_phi(a, b, eps)
        iterations_simple.append(iters_s)

    # Строим график
    plt.figure(figsize=(10, 5))
    plt.plot(eps_labels, iterations_newton, marker='o', linestyle='-', color='green', label='Метод Ньютона')
    plt.plot(eps_labels, iterations_simple, marker='s', linestyle='--', color='blue', label='Метод простых итераций')

    plt.xlabel('Точность ε')
    plt.ylabel('Число итераций')
    plt.title('Зависимость числа итераций от точности ε')
    plt.grid(True)
    plt.legend()
    plt.xticks(rotation=45)

    # Обеспечиваем адекватный масштаб
    ymin = min(iterations_newton + iterations_simple)
    ymax = max(iterations_newton + iterations_simple)
    plt.yticks(range(ymin, ymax + 1))

    plt.tight_layout()
    plt.show()


# Основная программа
if __name__ == "__main__":
    plot_functions()
    try:
        print("Введите интервал, в котором находится x:")
        a, b = map(float, input().split())
        print("Введите точность вычислений ε:")
        epsilon = float(input())

        # Метод Ньютона
        root, iterations = newton_method(a, b, epsilon)
        if root is not None:
            print("\n[Метод Ньютона]")
            print("Найденный x:", root)
            print("Значение функции:", f"{f(root):.30f}")
            print("Число итераций:", iterations)
        else:
            print("Метод Ньютона не сработал.")

        # Метод простых итераций
        root_iter, iter_iter = simple_iterations_manual_phi(a, b, epsilon)
        if root_iter is not None:
            print("\n[Метод простых итераций]")
            print("Найденный x:", root_iter)
            print("Значение функции:", f"{f(root_iter):.30f}")
            print("Число итераций:", iter_iter)
        else:
            print("Метод простых итераций не сработал.")

        # График зависимости числа итераций от точности
        plot_iterations_vs_epsilon(a, b)

    except Exception as e:
        print("Ошибка ввода или вычислений:", e)


        






