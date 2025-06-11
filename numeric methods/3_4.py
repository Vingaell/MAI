def get_i(x, x0):
    for i in range(len(x)):
        if x[i] == x0:
            return i
    return -1

def first_der(x, y, id_x, x0):
    if x0 in x and x0 != x[0] and x0 != x[-1]:
        print("\nТочка находится внутри отрезка")
        dxLeft = (y[id_x] - y[id_x - 1]) / (x[id_x] - x[id_x - 1])
        print("Значение левосторонней производной:", dxLeft)
        dxRight = (y[id_x + 1] - y[id_x]) / (x[id_x + 1] - x[id_x])
        print("Значение правосторонней производной:", dxRight)
        dxSecondAccuracy = (dxLeft + dxRight) / 2
        print("Значение производной второго порядка точности:", dxSecondAccuracy)
    else:
        print("\nТочка совпадает с правой границей отрезка. Найдем производную с первым порядком точности:")
        dx = (y[id_x] - y[id_x - 1]) / (x[id_x] - x[id_x - 1])
        print("Значение производной:", dx)
        if id_x < len(x) - 1:
            dxLeft = (y[id_x] - y[id_x - 1]) / (x[id_x] - x[id_x - 1])
            dxRight = (y[id_x + 1] - y[id_x]) / (x[id_x + 1] - x[id_x])
            dxSecondAccuracy = dxLeft + (dxRight - dxLeft) / (x[id_x + 1] - x[id_x - 1]) * (2 * x0 - x[id_x - 1] - x[id_x])
            print("Значение производной второго порядка точности:", dxSecondAccuracy)

def second_der(x, y, id_x):
    if 0 < id_x < len(x) - 1:
        dxdx = (2 * ((y[id_x + 1] - y[id_x]) / (x[id_x + 1] - x[id_x]) -
                     (y[id_x] - y[id_x - 1]) / (x[id_x] - x[id_x - 1])) /
                (x[id_x + 1] - x[id_x - 1]))
        print("Значение второй производной:", dxdx)
    else:
        print("Невозможно вычислить производную второго порядка")

# Данные
x = [-1, 0, 1, 2, 3]
y = [-0.5, 0, 0.5, 0.86603, 1]
x0 = 1

id_x = get_i(x, x0)
if id_x == -1:
    print("Точка не найдена в массиве x")
else:
    first_der(x, y, id_x, x0)
    second_der(x, y, id_x)
