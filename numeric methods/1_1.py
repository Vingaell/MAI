def read_matrix_from_file(filename):
    """Считывает матрицу A и вектор b из файла"""
    with open(filename, 'r') as f:
        lines = f.readlines()

    n = int(lines[0])  # Размерность матрицы
    A = [list(map(float, lines[i + 1].split())) for i in range(n)]
    b = [float(lines[n + 1 + i]) for i in range(n)]
    
    return n, A, b

def lu_decomposition_inplace(A):
    """LU-разложение"""
    n = len(A) 

    for k in range(n):
        for i in range(k + 1, n):
            A[i][k] /= A[k][k]  

            for j in range(k + 1, n):
                A[i][j] -= A[i][k] * A[k][j]  

    return A  

def solve_lu_system(A, b):
    """Решает систему LUx = b в одном шаге"""
    n = len(A)
    x = [0] * n

    # Прямой ход: решаем систему L * y = b
    for i in range(n):
        b[i] -= sum(A[i][j] * b[j] for j in range(i))

    # Обратный ход: решаем систему U * x = y
    for i in range(n - 1, -1, -1):
        b[i] = (b[i] - sum(A[i][j] * b[j] for j in range(i + 1, n))) / A[i][i]

    return b

def determinant(A):
    """Вычисляет определитель через произведение диагональных элементов U"""
    det = 1
    for i in range(len(A)):
        det *= A[i][i]
    return det

def inverse_matrix(A):
    """Вычисляет обратную матрицу через LU-разложение"""
    n = len(A)
    I = [[1 if i == j else 0 for j in range(n)] for i in range(n)]  # Единичная матрица
    inv_A = []

    for e in zip(*I):  # Берем столбцы единичной матрицы
        b = list(e)
        # Решаем систему LUx = b
        x = solve_lu_system(A, b)
        inv_A.append(x)

    return list(map(list, zip(*inv_A)))  # Транспонируем матрицу

def multiply_matrices(A, B):
    """Перемножает две квадратные матрицы"""
    n = len(A)
    return [[sum(A[i][k] * B[k][j] for k in range(n)) for j in range(n)] for i in range(n)]

def multiply_matrix_vector(A, x):
    """Перемножает матрицу A на вектор x"""
    return [sum(A[i][j] * x[j] for j in range(len(A))) for i in range(len(A))]

def print_matrix(matrix, name):
    """Выводим матрицу в консоль"""
    print(f"\n{name}:")
    for row in matrix:
        print(" ".join(map(str, row)))

def solve_system(filename):
    n, A, b = read_matrix_from_file(filename)
    
    # Копируем A, чтобы не изменять исходную матрицу
    A_original = [row[:] for row in A]

    # Выполняем LU-разложение
    lu_decomposition_inplace(A)

    # Выводим LU-матрицу
    print_matrix(A, "LU-разложение")

    # Решаем систему LUx = b
    x = solve_lu_system(A, b)

    # Вычисляем определитель
    det_A = determinant(A)
    
    # Вычисляем обратную матрицу
    inv_A = inverse_matrix(A)

    # Выводим результаты
    print("\nРешение СЛАУ:", x)
    print("Определитель:", det_A)
    
    print_matrix(inv_A, "Обратная матрица")

    # Вычисляем A * A^(-1)
    identity_check = multiply_matrices(A_original, inv_A)
    print_matrix(identity_check, "A * A^(-1)")

    # Вычисляем A * x
    Ax = multiply_matrix_vector(A_original, x)
    print("\nA * x:")
    for value in Ax:
        print(value)

# Запуск решения
solve_system("input.txt")





