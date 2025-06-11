import math

def find_max_upper_element(X):
    """
    Находит наибольший внедиагональный элемент в верхнем треугольнике матрицы.
    Возвращает индексы i, j и значение максимального элемента.
    """
    n = len(X)
    i_max, j_max = 0, 1
    max_elem = abs(X[0][1])
    for i in range(n):
        for j in range(i + 1, n):
            if abs(X[i][j]) > max_elem:
                max_elem = abs(X[i][j])
                i_max = i
                j_max = j
    return i_max, j_max, max_elem

def is_symmetric(A):
    """
    Проверяет, является ли матрица A симметричной.
    """
    n = len(A)
    for i in range(n):
        for j in range(i + 1, n):
            if A[i][j] != A[j][i]:
                return False
    return True

def rotation_method(A, eps):
    """
    Метод вращений (Якоби) для нахождения собственных значений и собственных векторов симметричной матрицы.
    """
    if not is_symmetric(A):
        raise ValueError("Матрица A должна быть симметричной")
    n = len(A)
    A_i = [row[:] for row in A]  # Копия матрицы A
    eigen_vectors = [[1.0 if i == j else 0.0 for j in range(n)] for i in range(n)]  # Единичная матрица
    iterations = 0
    
    while True:
        # Находим наибольший внедиагональный элемент
        i_max, j_max, max_off_diag = find_max_upper_element(A_i)
        if max_off_diag < eps:
            break
        
        # Вычисляем угол поворота
        if A_i[i_max][i_max] - A_i[j_max][j_max] == 0:
            phi = math.pi / 4
        else:
            phi = 0.5 * math.atan(2 * A_i[i_max][j_max] / (A_i[i_max][i_max] - A_i[j_max][j_max]))

        cos_phi = math.cos(phi)
        sin_phi = math.sin(phi)
        
        # Формируем матрицу поворота
        H = [[1.0 if i == j else 0.0 for j in range(n)] for i in range(n)]
        H[i_max][i_max] = cos_phi
        H[j_max][j_max] = cos_phi
        H[i_max][j_max] = -sin_phi
        H[j_max][i_max] = sin_phi
        
        print(f"Итерация {iterations}:")
        print("Матрица поворота H:")
        for row in H:
            print(row)
        
        # Обновляем элементы матрицы A
        for k in range(n):
            if k != i_max and k != j_max:
                A_ik = A_i[i_max][k] * cos_phi + A_i[j_max][k] * sin_phi
                A_jk = -A_i[i_max][k] * sin_phi + A_i[j_max][k] * cos_phi
                A_i[i_max][k] = A_ik
                A_i[j_max][k] = A_jk
                A_i[k][i_max] = A_ik  
                A_i[k][j_max] = A_jk

        # Обновляем диагональные элементы
        A_ii = A_i[i_max][i_max] * cos_phi**2 + 2 * A_i[i_max][j_max] * cos_phi * sin_phi + A_i[j_max][j_max] * sin_phi**2
        A_jj = A_i[i_max][i_max] * sin_phi**2 - 2 * A_i[i_max][j_max] * cos_phi * sin_phi + A_i[j_max][j_max] * cos_phi**2
        A_ij = 0  

        A_i[i_max][i_max] = A_ii
        A_i[j_max][j_max] = A_jj
        A_i[i_max][j_max] = A_ij
        A_i[j_max][i_max] = A_ij

        # Обновляем собственные векторы
        for k in range(n):
            eig_ik = eigen_vectors[k][i_max] * cos_phi + eigen_vectors[k][j_max] * sin_phi
            eig_jk = -eigen_vectors[k][i_max] * sin_phi + eigen_vectors[k][j_max] * cos_phi
            eigen_vectors[k][i_max] = eig_ik
            eigen_vectors[k][j_max] = eig_jk
        
        print("Обновленная матрица A:")
        for row in A_i:
            print(row)
        print("----------------------------------")
        
        iterations += 1
    
    eigen_values = [A_i[i][i] for i in range(n)]
    return eigen_values, eigen_vectors, iterations

def create_matrix(eigen_values, eigen_vectors):
    """
    Восстанавливает матрицу по собственным значениям и собственным векторам.
    """
    n = len(eigen_values)
    A = [[0.0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                A[i][j] += eigen_vectors[i][k] * eigen_values[k] * eigen_vectors[j][k]
    return A

def print_matrix(matrix):
    """
    Выводит матрицу в удобочитаемом формате.
    """
    for row in matrix:
        print(' '.join(f'{val:8.4f}' for val in row))

if __name__ == '__main__':
    # Чтение входных данных из файла
    with open('input1_4.txt', 'r') as file:
        lines = file.readlines()
    
    n = int(lines[0].strip())  # Размер матрицы
    A = [list(map(float, lines[i + 1].split())) for i in range(n)]  # Матрица
    eps = float(lines[n + 1].strip())  # Точность

    # Выполняем метод вращений
    eig_values, eig_vectors, iters = rotation_method(A, eps)
    print('Собственные значения:', eig_values)
    print('Собственные векторы:')
    for row in eig_vectors:
        print(row)
    print('Число итераций:', iters)

    # Восстанавливаем исходную матрицу по собственным векторам и значениям
    reconstructed_matrix = create_matrix(eig_values, eig_vectors)
    print("\nВосстановленная матрица из собственных значений и векторов:")
    print_matrix(reconstructed_matrix)