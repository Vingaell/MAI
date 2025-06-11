import matplotlib.pyplot as plt

x = [0, 1, 2, 3, 4]
f = [1.00000, 0.86603, 0.50000, 0.00000, -0.50000]
n = len(x) - 1
h = x[1] - x[0]
X_star = 1.5

a = [0]  # нижняя диагональ
b = [1]  # главная диагональ 
c = [0]  # верхняя диагональ
d = [0]  # правая часть

for i in range(1, n):
    a.append(1)
    b.append(4)
    c.append(1)
    d.append(3 * (f[i + 1] - 2 * f[i] + f[i - 1]))

# Метод прогонки для нахождения c
c_vals = [0] * (n + 1)  # с0 и сn = 0
# Прямой ход
for i in range(1, n):
    w = a[i] / b[i - 1]
    b[i] = b[i] - w * c[i - 1]
    d[i] = d[i] - w * d[i - 1]

# Обратный ход
c_vals[n - 1] = d[n - 1] / b[n - 1]
for i in range(n - 2, 0, -1):
    c_vals[i] = (d[i] - c[i] * c_vals[i + 1]) / b[i]

# c0 и cn по краям равны нулю (условие натурального сплайна)
c_vals[0] = 0
c_vals[n] = 0

# Вычисляем коэффициенты a, b, d
a_coeff = []
b_coeff = []
d_coeff = []

for i in range(1, n + 1):
    ai = f[i - 1]
    ci = c_vals[i]
    ci_prev = c_vals[i - 1]
    di = (ci - ci_prev) / (3 * h)
    bi = (f[i] - f[i - 1]) / h - (h / 3) * (2 * ci_prev + ci)
    
    a_coeff.append(ai)
    b_coeff.append(bi)
    d_coeff.append(di)

# Найдём нужный интервал
for i in range(1, n + 1):
    if x[i - 1] <= X_star <= x[i]:
        dx = X_star - x[i - 1]
        S = (a_coeff[i - 1] +
             b_coeff[i - 1] * dx +
             c_vals[i - 1] * dx ** 2 +
             d_coeff[i - 1] * dx ** 3)
        print(f"S({X_star}) = {S}")
        break

# Построение графика
points_x = []
points_y = []

for i in range(1, n + 1):
    xi = x[i - 1]
    xf = x[i]
    a_i = a_coeff[i - 1]
    b_i = b_coeff[i - 1]
    c_i = c_vals[i - 1]
    d_i = d_coeff[i - 1]
    
    step = 0.01
    t = xi
    while t <= xf:
        dx = t - xi
        y = a_i + b_i * dx + c_i * dx ** 2 + d_i * dx ** 3
        points_x.append(t)
        points_y.append(y)
        t += step

plt.figure(figsize=(8, 5))
plt.plot(points_x, points_y, label='Cubic spline', color='blue')
plt.scatter(x, f, color='red', label='Data points')
plt.scatter([X_star], [S], color='green', s=80, zorder=5, label=f'S({X_star}) = {S:.5f}')
plt.title('Natural Cubic Spline Interpolation')
plt.xlabel('x')
plt.ylabel('S(x)')
plt.legend()
plt.grid(True)
plt.show()
