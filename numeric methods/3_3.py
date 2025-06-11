import matplotlib.pyplot as plt

# Исходные данные
x_vals = [-1, 0, 1, 2, 3, 4]
y_vals = [0.86603, 1, 0.86603, 0.5, 0, -0.5]

n = len(x_vals)

# МНК для многочлена первой степени: y = a + b*x
def least_squares_linear(x, y):
    sum_x = sum(x)
    sum_y = sum(y)
    sum_x2 = sum(xi**2 for xi in x)
    sum_xy = sum(x[i] * y[i] for i in range(n))

    A = [[n, sum_x],
         [sum_x, sum_x2]]
    B = [sum_y, sum_xy]

    # Решим систему методом Крамера
    detA = A[0][0] * A[1][1] - A[0][1] * A[1][0]
    detA1 = B[0] * A[1][1] - A[0][1] * B[1]
    detA2 = A[0][0] * B[1] - B[0] * A[1][0]

    a = detA1 / detA
    b = detA2 / detA

    # Сумма квадратов ошибок
    error = sum((y[i] - (a + b * x[i]))**2 for i in range(n))

    return a, b, error

# МНК для многочлена второй степени: y = a + b*x + c*x^2
def least_squares_quadratic(x, y):
    sum_x = sum(x)
    sum_x2 = sum(xi**2 for xi in x)
    sum_x3 = sum(xi**3 for xi in x)
    sum_x4 = sum(xi**4 for xi in x)
    sum_y = sum(y)
    sum_xy = sum(x[i] * y[i] for i in range(n))
    sum_x2y = sum((x[i]**2) * y[i] for i in range(n))

    A = [
        [n, sum_x, sum_x2],
        [sum_x, sum_x2, sum_x3],
        [sum_x2, sum_x3, sum_x4]
    ]
    B = [sum_y, sum_xy, sum_x2y]

    # Решим систему методом Крамера
    def determinant(m):
        return (
            m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
            - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
            + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0])
        )

    def replace_column(matrix, col_idx, new_col):
        return [
            [new_col[i] if j == col_idx else matrix[i][j] for j in range(3)]
            for i in range(3)
        ]

    detA = determinant(A)
    detA0 = determinant(replace_column(A, 0, B))
    detA1 = determinant(replace_column(A, 1, B))
    detA2 = determinant(replace_column(A, 2, B))

    a = detA0 / detA
    b = detA1 / detA
    c = detA2 / detA

    # Сумма квадратов ошибок
    error = sum((y[i] - (a + b * x[i] + c * x[i]**2))**2 for i in range(n))

    return a, b, c, error

# Расчет коэффициентов и ошибок
a1, b1, err1 = least_squares_linear(x_vals, y_vals)
a2, b2, c2, err2 = least_squares_quadratic(x_vals, y_vals)

# Вывод результатов
print(f"Многочлен 1-й степени: f(x) = {a1:.5f} + {b1:.5f} * x")
print(f"Многочлен 2-й степени: f(x) = {a2:.5f} + {b2:.5f} * x + {c2:.5f} * x^2\n")
print(f"Сумма квадратов ошибок (1-й степени): {err1:.5f}")
print(f"Сумма квадратов ошибок (2-й степени): {err2:.5f}")

# Создание значений x для построения графика
x_min = min(x_vals) - 1
x_max = max(x_vals) + 1
x_plot = [x_min + i * (x_max - x_min) / 300 for i in range(301)]

# Вычисление значений многочленов
y_lin = [a1 + b1 * x for x in x_plot]
y_quad = [a2 + b2 * x + c2 * x**2 for x in x_plot]

# Построение графика
plt.plot(x_plot, y_lin, label='1-я степень', color='blue')
plt.plot(x_plot, y_quad, label='2-я степень', color='green')
plt.scatter(x_vals, y_vals, label='Точки', color='red')
plt.legend()
plt.title("Аппроксимация МНК")
plt.grid(True)
plt.xlabel("x")
plt.ylabel("y")
plt.show()

