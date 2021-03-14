import random
import math

n = int(input("Введите n: "))

m = float(input("Введите процент разреженности в долях: "))

w = int(input("0 - обычная матрица и вектор, 1 - разреженная: "))

#кол-во нулевых элементов
k = math.ceil(n * n * m)

if w == 1:
    f = open("shared/objects_" + str(n) + "_" + str(int(m * 100)) + ".txt", "w")
    a = [-1 for i in range(n * n)]

    for i in range(k):
        pos = random.randint(0, n * n - 1)
        while a[pos] == 0:
            pos = random.randint(0, n * n - 1)
        a[pos] = 0

    for i in range(n * n):
        if a[i] != 0:
            x = random.randint(-10, 10)
            while x == 0:
                x = random.randint(-10, 10)
            a[i] = x
            
    v = [-1 for i in range(n)]

    k = math.ceil(n * m)

    for i in range(k):
        pos = random.randint(0, n - 1)
        while v[pos] == 0:
            pos = random.randint(0, n - 1)
        v[pos] = 0

    for i in range(n):
        if v[i] != 0:
            x = random.randint(-10, 10)
            while x == 0:
                x = random.randint(-10, 10)
            v[i] = x
    #сгенерировала обычную матрицу, конвертирую в 3 объекта
    a_n = []
    a_j = []
    a_i = []
    v_a = []
    v_i = []
    for i in range(n*n):
        if (a[i] != 0):
            a_n.append(a[i])
            a_j.append(i % n + 1)
            
    a_i = [0 for i in range(n)]
    a_i.append(len(a_n) + 1)
    step = 0
    for i in range(n):
        j = 0
        while j < n and a[j + i * n] == 0:
            j += 1
        if j != n:
            step += 1
            a_i[i] = step
        while j < n:
            if a[j + i * n] != 0:
                step += 1
            j += 1
            
    for i in range(n):
        if (v[i] != 0):
            v_a.append(v[i])
            v_i.append(len(v_a))

    i = 0
    while i <= n:
        if a_i[i] != 0:
            j = i - 1
            while j >= 0 and a_i[j] == 0:
                a_i[j] = a_i[i]
                j -= 1
        i += 1

    for i in range(len(a_n)):
        f.write(str(a_n[i]))
        if i != (len(a_n) - 1):
            f.write(" ")
    f.write("\n")
    
    for i in range(len(a_j)):
        f.write(str(a_j[i]))
        if i != (len(a_j) - 1):
            f.write(" ")
    f.write("\n")

    for i in range(len(a_i)):
        f.write(str(a_i[i]))
        if i != (len(a_i) - 1):
            f.write(" ")
    f.write("\n")

    for i in range(len(v_a)):
        f.write(str(v_a[i]))
        if i != (len(v_a) - 1):
            f.write(" ")
    f.write("\n")

    for i in range(len(v_i)):
        f.write(str(v_i[i]))
        if i != (len(v_i) - 1):
            f.write(" ")
    f.close()

if w == 0:

    f = open("shared/usual_" + str(n) + "_" + str(int(m * 100)) + ".txt", "w")

    a = [-1 for i in range(n * n)]

    for i in range(k):
        pos = random.randint(0, n * n - 1)
        while a[pos] == 0:
            pos = random.randint(0, n * n - 1)
        a[pos] = 0

    for i in range(n * n):
        if a[i] != 0:
            x = random.randint(-10, 10)
            while x == 0:
                x = random.randint(-10, 10)
            a[i] = x
            
    v = [-1 for i in range(n)]

    k = math.ceil(n * m)

    for i in range(k):
        pos = random.randint(0, n - 1)
        while v[pos] == 0:
            pos = random.randint(0, n - 1)
        v[pos] = 0

    for i in range(n):
        if v[i] != 0:
            x = random.randint(-10, 10)
            while x == 0:
                x = random.randint(-10, 10)
            v[i] = x

    for i in range(n * n):
        f.write(str(a[i]))
        if i % n != (n - 1):
            f.write(" ")
        else:
            f.write("\n")

    for i in range(n):
        f.write(str(v[i]))
        if i != (n - 1):
            f.write(" ")

f.close()
