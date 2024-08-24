from cs50 import get_float

c = 0

while True:
    d = get_float("Change: ")
    if d > 0:
        break

change = round(d * 100)

while change > 0:
    while change >= 25:
        c = c + 1
        change = change - 25
    while change >= 10:
        c = c + 1
        change = change - 10
    while change >= 5:
        c = c + 1
        change = change - 5
    while change >= 1:
        c = c + 1
        change = change - 1

print(c)
