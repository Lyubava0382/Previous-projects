import re
import numpy as np
import math
from sklearn.metrics import r2_score
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

def read(path):
    f = open(path)
    array = []
    l = [line.strip() for line in f]
    for i in range(len(l)):
        str = [float(s) for s in re.findall(r'-?\d+\.?\d*', l[i])]
        little_array = []
        little_array.append(str[0])
        little_array.append(str[1])
        little_array.append(str[2])
        array.append(little_array)
    return array


def decompose_to_LU(a):
    lu_matrix = np.matrix(np.zeros([a.shape[0], a.shape[1]]))
    n = a.shape[0]
    for k in range(n):
        for j in range(k, n):
            lu_matrix[k, j] = a[k, j] - lu_matrix[k, :k] * lu_matrix[:k, j]
        for i in range(k + 1, n):
            lu_matrix[i, k] = (a[i, k] - lu_matrix[i, : k] * lu_matrix[: k, k]) / lu_matrix[k, k]
    return lu_matrix

def solve_LU(lu_matrix, b):
    y = np.matrix(np.zeros([lu_matrix.shape[0], 1]))
    for i in range(y.shape[0]):
        y[i, 0] = b[i, 0] - lu_matrix[i, :i] * y[:i]
    x = np.matrix(np.zeros([lu_matrix.shape[0], 1]))
    for i in range(1, x.shape[0] + 1):
        x[-i, 0] = (y[-i] - lu_matrix[-i, -i:] * x[-i:, 0] )/ lu_matrix[-i, -i]
    return x

def regression(X,Y):
    A = np.dot(X.transpose(), X)
    b = np.dot(X.transpose(), Y)
    # LU - разложение в одну матрицу
    LU = decompose_to_LU(A)
    # Вектор решений
    B = solve_LU(LU, b)
    return np.array(B)

def solve_regression(X,B):
    res = np.dot(X,B)
    return res

def polynom_f(x,y):
    X_poly = np.array([[1, i, i**2, i**3, i**4] for i in x])
    Y = np.array([[i] for i in y])  # Столбец зависящих величин
    B_polynomical = regression(X_poly, Y)
    solve_Y_polynomical = solve_regression(X_poly, B_polynomical)[:, 0]

    #print("Матрица наблюдений:")
    #for i in x:
    #    print(i)

    #print("Матрица наблюдений + добавленные переменные для полиноминализации:")
    #for i in X_poly:
    #    print(i)

    #print("Столбец значений:")
    #for i in Y:
    #    print(i)

    # Полиномиальная регрессия
    #print("Полиноминальная регрессия")
    #print(solve_Y_polynomical)

    return solve_Y_polynomical

def rms_f(arrays):
    summ_for_rms = 0
    for array in arrays:
        summ_for_rms += (array[5]) ** 2
    return math.sqrt(summ_for_rms / (len(arrays) - 1))

if __name__ == '__main__':
    data = read('./Считывание/demo.txt')
    arrays = data
    x = [i[1] for i in data]
    y = [i[2] for i in data]
    polynom = np.polyfit(x, y, deg=4)
    for dt in data:
        dt.append(np.polyval(polynom, dt[1]))
    for index in range(len(arrays)):
        arrays[index].append(index)
    lenght = 0
    arrays3 = []
    while len(arrays) != lenght:
        for index in range(len(arrays)):
            del arrays[index][5:]
        x = [i[1] for i in arrays]
        y = [i[2] for i in arrays]
        summ = 0
        count = 0
        poly = []
        poly = polynom_f(x, y)
        for index in range(len(arrays)):
            arrays[index].append(arrays[index][2] - poly[index])
            arrays[index].append(poly[index])
        rms = rms_f(arrays)
        lenght = len(arrays)
        arrays2 = []
        for index in range(len(arrays)):
            little_array = []
            little_array.append(arrays[index][0])
            little_array.append(arrays[index][1])
            little_array.append(arrays[index][2])
            little_array.append(arrays[index][3])
            little_array.append(arrays[index][4])
            little_array.append(arrays[index][5])
            if abs(arrays[index][-2]) < 3*rms:
                arrays2.append(little_array)
            else:
                arrays3.append(little_array)
        del arrays
        arrays = arrays2
    intervals = []
    intervals_data = []
    littlearray = []
    for index in range(len(arrays)):
        if index == 0:
            littlearray.append(arrays[index])
        else:
            if arrays[index][0]%1 - arrays[index-1][0]%1 > 0.0005 or index == len(arrays)-1:
                intervals.append(littlearray)
                littlearray = []
            littlearray.append(arrays[index])
    for interval in range(len(intervals)):
        mediana = (intervals[interval][-1][1] - intervals[interval][0][1])/2 + intervals[interval][0][1]
        normal = 0
        normal = intervals[interval][0]
        for step in intervals[interval]:
            if  abs(step[1] - mediana) < abs(normal[1] - mediana): # and step[1] % 0.000001 == 0:
                normal = step
        intervals_data.append(normal)
    file = open("demo2.txt", "w")
    for interval in intervals:
        rms_for_interval = rms_f(interval)
        for lttlarray in interval:
            lttlarray.append(rms_for_interval)
            file.write(f'{lttlarray[0]}\t{lttlarray[1]}\t{lttlarray[2]}\t{lttlarray[-1]}\n')
    for index in range(len(intervals)):
        intervals_data[index].append(rms_f(intervals[index]))
        print(f'Нормальная точка {index+1} интервала:')
        print(f'Время: {intervals_data[index][0]}\tЗначение полинома:{intervals_data[index][3]}\tRms:{intervals_data[index][-1]}\n')
    x_polynom = np.array([i for i in range(len(data))])
    y_polynom = np.array([i[5] for i in data])
    x_array = np.array([i[4] for i in arrays])
    y_array = np.array([i[2] for i in arrays])
    x_no = np.array([i[4] for i in arrays3])
    y_no = np.array([i[2] for i in arrays3])
    plt.scatter(x_array, y_array, label='Оставленные точки', c="m", lw=0.001)
    plt.scatter(x_no, y_no, label='Точки-выбросы',  c="b", lw=0.001)
    plt.scatter(x_polynom, y_polynom, label='Значение полинома', c="y", lw=0.001)
    plt.legend()
    plt.show()
    file.close()