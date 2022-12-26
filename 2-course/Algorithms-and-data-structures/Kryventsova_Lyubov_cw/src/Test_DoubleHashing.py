import matplotlib.pyplot as plt
from DoubleHashing import *
import time

from random import randint
hash_table = DoubleHashing(1009)

# Линейная зависимость
range1 = [i for i in range(2000)]
n = [randint(1, 1009) for i in range(2000)]
find_array = []
remove_array = []
insert_array = []

for i in n:
    hash_table.Insert(i, 'Hello!!')

for i in range1:
    start_time = time.time_ns()
    hash_table.FindKey(i)
    end_time = time.time_ns()
    find_array.append(end_time - start_time)


for i in range1:
    start_time = time.time_ns()
    hash_table.Remove(i)
    end_time = time.time_ns()
    remove_array.append(end_time - start_time)


for i in range1:
    start_time = time.time_ns()
    hash_table.Insert(i, 'Hello!')
    end_time = time.time_ns()
    insert_array.append(end_time - start_time)


remove_array.reverse()


# Построение графика
pl1 = plt.subplot(2,1,2)
pl2 = plt.subplot(2,1,1)
plt.title("Исследование сложности операций с двойным хэшированием в  сред. случае") # заголовок
pl1.set_xlabel("Количество элементов")         # ось абсцисс
pl2.set_ylabel("Время, нс")    # ось ординат
pl1.grid()
pl2.grid()   # включение отображение сетки
#pl1.scatter(range1, find_array, s = 5, color = ["magenta"])  # построение графика
pl1.scatter(range1, insert_array, s = 5, color = ["blue"])
pl2.scatter(range1, remove_array, s = 5, color = ["red"])  # построение графика
pl1.legend([ "Сложность вставки в сред. случае"])
pl2.legend([ "Сложность удаления в сред. случае"])

plt.show()