def read_matrix_from_file(filename):
    """Считывает матрицу A, вектор B и точность из файла."""
    with open(filename, 'r') as f:
        lines = f.readlines()

    n = int(lines[0].strip())  # Размерность матрицы
    A = [list(map(float, lines[i + 1].split())) for i in range(n)]  # Матрица A
    B = [float(lines[n + 1 + i]) for i in range(n)]  # Вектор B
    eps = float(lines[-1].strip())  # Точность

    return n, A, B, eps


def check_conditions(A):
    """Проверяет диагональное преобладание."""
    n = len(A)
    has_strict = False  

    for i in range(n):
        sum_other = sum(abs(A[i][j]) for j in range(n) if i != j)
        if abs(A[i][i]) > sum_other:
            has_strict = True
        if abs(A[i][i]) <= sum_other:
            check_column_conditions(A)
            return

    if not has_strict:
        check_column_conditions(A)


def check_column_conditions(A):
    """Проверяет диагональное преобладание по столбцам."""
    n = len(A)
    has_strict = False

    for j in range(n):
        sum_other = sum(abs(A[i][j]) for i in range(n) if i != j)
        if abs(A[j][j]) > sum_other:
            has_strict = True
        if abs(A[j][j]) <= sum_other:
            print("⚠️  Предупреждение: диагональное преобладание не выполнено!")
            return
        
    if not has_strict:
        print("⚠️  Предупреждение: диагональное преобладание не выполнено!")


def simple_iterations(A, B, eps):
    """Решает систему методом простых итераций."""
    n = len(A)
    x = [0] * n
    iterations = 0
    print("\n🔹 Метод простых итераций:")

    while True:
        x_new = [0] * n
        for i in range(n):
            x_new[i] = (B[i] - sum(A[i][j] * x[j] for j in range(n) if j != i)) / A[i][i]

        error = sum((x_new[i] - x[i]) ** 2 for i in range(n)) ** 0.5
        x = x_new
        iterations += 1

        print(f"Шаг {iterations}: x = {x}, ошибка = {error:.6f}")

        if error < eps:
            break

    return x, iterations


def seidel_method(A, B, eps):
    """Решает систему методом Зейделя."""
    n = len(A)
    x = [0] * n
    iterations = 0
    print("\n🔹 Метод Зейделя:")

    while True:
        x_new = x[:]
        for i in range(n):
            x_new[i] = (B[i] - sum(A[i][j] * x_new[j] if j < i else A[i][j] * x[j] for j in range(n) if j != i)) / A[i][i]

        error = sum((x_new[i] - x[i]) ** 2 for i in range(n)) ** 0.5
        x = x_new
        iterations += 1

        print(f"Шаг {iterations}: x = {x}, ошибка = {error:.6f}")

        if error < eps:
            break

    return x, iterations


def multiply_matrix_vector(A, x):
    """Перемножает матрицу A на вектор x, возвращая получившийся вектор."""
    return [sum(A[i][j] * x[j] for j in range(len(A))) for i in range(len(A))]


def solve_system(filename):
    """Считывает матрицу, проверяет условия, решает систему и выводит результаты."""
    n, A, B, eps = read_matrix_from_file(filename)

    # Проверка диагонального преобладания
    check_conditions(A)

    # Метод простых итераций
    x_si, iters_si = simple_iterations(A, B, eps)
    print("\nРешение методом простых итераций:", x_si)
    print("Число итераций:", iters_si)
    print("Проверка A * x =", multiply_matrix_vector(A, x_si))

    # Метод Зейделя
    x_seidel, iters_seidel = seidel_method(A, B, eps)
    print("\nРешение методом Зейделя:", x_seidel)
    print("Число итераций:", iters_seidel)
    print("Проверка A * x =", multiply_matrix_vector(A, x_seidel))


# Запуск решения
solve_system("input1_3.txt")



