import random
f = open("data.txt", "w")

cars = ["BMW", "Audi", "Renault", "Lexus", "Citroen"]

country = ["Japan", "USA", "Germany", "China", "Russia", "France"]

prices = []
for i in range(30):
    prices.append(i * 10)

years = []
for i in range(50):
    years.append(1970 + i)

warranty = []
for i in range(30):
    warranty.append(i + 1)

colors = ["black", "white", "yellow", "red", "green", "blue"]

mileage = []
for i in range(10000, 20000):
    mileage.append(i)

repairs = [0]

owners = [2]

for i in range(40):
    f.write(random.choice(cars) + "\n" + random.choice(country) + "\n" + str(random.choice(prices)) + "\n" +
            random.choice(colors) + "\n")
    f.write(str(random.choice(years)) + "\n" + str(random.choice(mileage)) + "\n" + str(random.choice(repairs)) + "\n" + str(random.choice(owners)) + "\n\n")

f.close()
