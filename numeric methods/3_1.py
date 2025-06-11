import math

pi = math.pi

points_A = [0, pi/6, 2*pi/6, 3*pi/6]
points_B = [0, pi/6, 5*pi/12, pi/2]
x_star = pi/4

def f(x):
    return math.cos(x)

def get_y(points):
    return [f(x) for x in points]

def lagrange_polynomial(X, Y, x_star):
    n = len(X)
    def L_i(i, x):
        res = 1.0
        for j in range(n):
            if j != i:
                res *= (x - X[j]) / (X[i] - X[j])
        return res
    value = 0.0
    for i in range(n):
        value += Y[i] * L_i(i, x_star)
    return value

def lagrange_poly_str(X, Y):
    n = len(X)
    terms = []
    for i in range(n):
        coef = Y[i]
        factors = ''
        for j in range(n):
            if j != i:
                factors += f"(x-{X[j]:.2f})"
        sign = '+' if coef >= 0 else '-'
        terms.append(f" {sign} {abs(coef):.2f}*{factors}")
    return "L(x) =" + "".join(terms)

def divided_differences(X, Y):
    n = len(X)
    dd_table = [y for y in Y]
    coeffs = [dd_table[0]]
    for level in range(1, n):
        new_dd = []
        for i in range(n - level):
            val = (dd_table[i+1] - dd_table[i]) / (X[i+level] - X[i])
            new_dd.append(val)
        coeffs.append(new_dd[0])
        dd_table = new_dd
    return coeffs

def newton_poly_value(X, coeffs, x):
    n = len(coeffs)
    res = coeffs[0]
    prod = 1.0
    for i in range(1, n):
        prod *= (x - X[i-1])
        res += coeffs[i] * prod
    return res

def newton_poly_str(X, coeffs):
    n = len(coeffs)
    terms = [f"{coeffs[0]:.2f}"]
    for i in range(1, n):
        factors = ''.join([f"(x-{X[j]:.2f})" for j in range(i)])
        sign = '+' if coeffs[i] >= 0 else '-'
        terms.append(f" {sign} {abs(coeffs[i]):.2f}*{factors}")
    return "P(x) = " + " +".join(terms)

def abs_error(true_val, approx_val):
    return abs(true_val - approx_val)

def process_points(name, X):
    Y = get_y(X)
    true_val = f(x_star)

    print(f"Точки {name}")
    # Лагранж
    L_val = lagrange_polynomial(X, Y, x_star)
    print("Полином:")
    print(lagrange_poly_str(X, Y))
    print(f"Значение полинома в точке X* = {L_val}")
    print(f"Значение функции в точке X* = {true_val}")
    print(f"Абсолютная погрешность в точке = {abs_error(true_val, L_val)}\n")

    # Ньютона
    coeffs = divided_differences(X, Y)
    N_val = newton_poly_value(X, coeffs, x_star)
    print("Полином:")
    print(newton_poly_str(X, coeffs))
    print(f"Значение полинома в точке X* = {N_val}")
    print(f"Значение функции в точке X* = {true_val}")
    print(f"Абсолютная погрешность в точке = {abs_error(true_val, N_val)}\n")

process_points("A", points_A)
process_points("B", points_B)

