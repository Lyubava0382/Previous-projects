import math
import sys
sys.setrecursionlimit(100000) #max глубина рекурсии

class DoubleHashing:
    def __init__(self, size):
        self.Size = size
        self.FixSize()
        self.Hash_Table = [[], ] * self.Size
        self.Overflow = 0

    def Hashing1(self, key): #Метод середины квадрата
        key *= key
        key >>= 11  # Отбрасываем 11 младших бит
        return key % 1024 # Возвращаем 10 младших бит

    def Hashing2(self, key):  # Метод деления
        return key % self.Size

    def Insert(self, key, data, i=0):
        percent_overflow = 100 * (2/3)
        percent_one = 100
        if i >= self.Size or self.Overflow >= percent_overflow:
            self.Size = self.Size * 2
            self.FixSize()
            previous_Hash_Table = self.Hash_Table
            self.Hash_Table = [[], ] * self.Size
            self.Overflow = 0
            for key_index in range(len(previous_Hash_Table)):
                if previous_Hash_Table[key_index]:
                    self.Insert(previous_Hash_Table[key_index][0], previous_Hash_Table[key_index][1], 0)
            self.Insert(key, data, 0)
        else:
            index = (self.Hashing1(key) + i * self.Hashing2(key)) % self.Size
            if self.Hash_Table[index] and self.Hash_Table[index] != [None]:
                if self.Hash_Table[index][0] == key:
                    self.Hash_Table[index] = [key, data]
                else:
                    i += 1
                    self.Insert(key, data, i)
            else:
                self.Hash_Table[index] = [key, data]
                self.Overflow += round( percent_one / self.Size)


    def Remove(self, key, i=0):
        if i < self.Size:
            index = (self.Hashing1(key) + i * self.Hashing2(key)) % self.Size
            if self.Hash_Table[index]:
                if self.Hash_Table[index][0] == key:
                    self.Hash_Table[index] = [None]
                else:
                    i += 1
                    self.Remove(key, i)

    def InPrimes(self) -> int:
        if self.Size == 1 or self.Size == 0:
            return 0
        for i in range(2, self.Size // 2):
            if self.Size % i == 0:
                return 0
        return 1

    def FixSize(self):
        if self.Size % 2 == 0:
            self.Size += 1
        while not self.InPrimes():
            self.Size += 2
        return self.Size


    def FindKey(self, key, i=0):
        index = (self.Hashing1(key) + i * self.Hashing2(key)) % self.Size  # DF
        if i >= self.Size or not self.Hash_Table[index]:
            return "None"
        else:
            if self.Hash_Table[index][0] == key:
                return self.Hash_Table[index][1]
            else:
                i += 1
                return self.FindKey(key, i)



hash = DoubleHashing(10)

for i in range(10):
    hash.Insert(i,str(i))
print(hash.Hash_Table)
hash.Insert(9,9)
print(hash.Hash_Table)
hash.Insert(11,'WoW')
print(hash.FindKey(10))
print(hash.FindKey(11))
hash.Remove(2)
print(hash.Hash_Table)
