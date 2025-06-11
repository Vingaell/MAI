def read_matrix_from_file(filename):
    """Считывает трехдиагональную матрицу A и вектор d из файла."""
    with open(filename, 'r') as f:
        lines = f.readlines()

    n = int(lines[0]) 

    A = [list(map(float, lines[i + 1].split())) for i in range(n)]
    d = [float(lines[n + 1 + i]) for i in range(n)]
    
    return n, A, d

def check_conditions(A):
    """Проверяет необходимые условия для метода прогонки."""
    n = len(A)

    # Проверка на трехдиагональность 
    for i in range(n):
        for j in range(n):
            if abs(i - j) > 1 and abs(A[i][j]) > 1e-9:
                raise ValueError("Ошибка: матрица не является трехдиагональной.")

    # Проверка наличия нулей на главной диагонали 
    if any(abs(A[i][i]) < 1e-9 for i in range(n)):
        raise ValueError("Ошибка: на главной диагонали есть нулевой элемент.")
    
def check_sufficient_conditions(A):
    """Проверяет достаточное условие диагонального преобладания."""
    n = len(A)
    ok = True
    ok2 = False

    for i in range(1, n-1):
        if abs(A[i][i]) <= abs(A[i][i-1]) + abs(A[i][i+1]):
            ok = False
        if abs(A[i][i]) > abs(A[i][i-1]) + abs(A[i][i+1]):
            ok2 = True

    if abs(A[0][0]) <= abs(A[0][1]):
        ok = False
    if abs(A[0][0]) > abs(A[0][1]):
        ok2 = True

    if abs(A[n-1][n-1]) <= abs(A[n-1][n-2]):
        ok = False
    if abs(A[n-1][n-1]) > abs(A[n-1][n-2]):
        ok2 = True

    if not ok or not ok2:
        print("⚠️  Предупреждение: достаточное условие диагонального преобладания не выполнено!")


def extract_tridiagonal_vectors(A, d):
    """Извлекает коэффициенты трехдиагональной матрицы в векторы lower, main, upper и d."""
    n = len(A)
    lower = [0] + [A[i][i - 1] for i in range(1, n)]  # Нижняя диагональ
    main = [A[i][i] for i in range(n)]               # Главная диагональ
    upper = [A[i][i + 1] for i in range(n - 1)] + [0] # Верхняя диагональ 
    
    return lower, main, upper, d

def thomas_algorithm(lower, main, upper, d):
    """Решает СЛАУ с трехдиагональной матрицей методом прогонки."""
    n = len(main)
    
    # Прямой ход
    p = [0] * n
    q = [0] * n
    
    p[0] = -upper[0] / main[0]
    q[0] = d[0] / main[0]
    
    for i in range(1, n):
        denominator = main[i] + lower[i] * p[i - 1]
        p[i] = -upper[i] / denominator if i < n - 1 else 0
        q[i] = (d[i] - lower[i] * q[i - 1]) / denominator

    # Обратный ход
    x = [0] * n
    x[n - 1] = q[n - 1]
    
    for i in range(n - 2, -1, -1):
        x[i] = p[i] * x[i + 1] + q[i]
    
    return x

def multiply_matrix_vector(A, x):
    """Перемножает матрицу A на вектор x, возвращая получившийся вектор."""
    return [sum(A[i][j] * x[j] for j in range(len(A))) for i in range(len(A))]

def solve_system(filename):
    """Читает матрицу, проверяет условия, решает систему и выводит результат."""
    n, A, d = read_matrix_from_file(filename)

    # Проверяем необходимые условия метода прогонки
    check_conditions(A)
    
    # Проверяем достаточное условие
    check_sufficient_conditions(A)

    # Извлекаем векторы lower, main, upper и d
    lower, main, upper, d = extract_tridiagonal_vectors(A, d)

    # Решаем систему
    x = thomas_algorithm(lower, main, upper, d)

    # Выводим x 
    print("\nРешение СЛАУ:")
    for value in x:
        print(f"{value:.1f}")

    # A * x
    Ax = multiply_matrix_vector(A, x)
    print("\nПроверка: A * x =")
    for value in Ax:
        print(f"{value:.1f}")

# Запуск решения
solve_system("input1.2txt")





