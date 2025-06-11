def f(x):
    return x / (3 * x + 4)**2

def rectangle_method(a, b, h):
    n = int((b - a) / h)
    result = 0
    for i in range(n):
        xi = a + i * h
        xi1 = xi + h
        midpoint = (xi + xi1) / 2
        result += f(midpoint)
    return result * h

def trapezoid_method(a, b, h):
    n = int((b - a) / h)
    result = (f(a) + f(b)) / 2
    for i in range(1, n):
        x = a + i * h
        result += f(x)
    return result * h

def simpson_method(a, b, h):
    n = int((b - a) / h)
    if n % 2 == 1:
        n += 1  
    h = (b - a) / n
    result = f(a) + f(b)
    for i in range(1, n):
        x = a + i * h
        coef = 4 if i % 2 == 1 else 2
        result += coef * f(x)
    return result * h / 3

def runge_romberg(Fh, Fkh, k, p):
    return Fh + (Fh - Fkh) / (k**p - 1)

# Параметры задачи
a = 0
b = 4
h1 = 1
h2 = 0.5
k = int(h1 / h2)

# Прямоугольники
R1 = rectangle_method(a, b, h1)
R2 = rectangle_method(a, b, h2)
R_rr = runge_romberg(R2, R1, k, 2)
R_err = abs(R_rr - R2)

# Трапеции
T1 = trapezoid_method(a, b, h1)
T2 = trapezoid_method(a, b, h2)
T_rr = runge_romberg(T2, T1, k, 2)
T_err = abs(T_rr - T2)

# Симпсон
S1 = simpson_method(a, b, h1)
S2 = simpson_method(a, b, h2)
S_rr = runge_romberg(S2, S1, k, 4)
S_err = abs(S_rr - S2)

# Результаты
print("Прямоугольники:")
print(f" h1={h1}: {R1}, h2={h2}: {R2}, уточнённый: {R_rr}, ошибка: {R_err}")

print("\nТрапеции:")
print(f" h1={h1}: {T1}, h2={h2}: {T2}, уточнённый: {T_rr}, ошибка: {T_err}")

print("\nСимпсон:")
print(f" h1={h1}: {S1}, h2={h2}: {S2}, уточнённый: {S_rr}, ошибка: {S_err}")
