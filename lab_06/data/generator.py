import random


n = 10
string = ""
for i in range(n):
    x = random.randint(0, 5000)
    string += str(x) + "\n"

f = open("file10.txt", "w")
for i in range(0, len(string) - 1):
    f.write(string[i])

f.close()

n = 100
string = ""
for i in range(n):
    x = random.randint(0, 5000)
    string += str(x) + "\n"

f = open("file100.txt", "w")
for i in range(0, len(string) - 1):
    f.write(string[i])

f.close()

n = 1000
string = ""
for i in range(n):
    x = random.randint(0, 5000)
    string += str(x) + "\n"
    
f = open("file1000.txt", "w")
for i in range(0, len(string) - 1):
    f.write(string[i])

f.close()
