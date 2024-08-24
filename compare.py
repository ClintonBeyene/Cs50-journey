from cs50 import get_int

x = get_int ("what's x? ")
y = get_int ("what's y? ")

if (x < y):
    print("x is less than y")
elif (x > y):
    print("x is gretar than y")
else:
    print("x is equal to y")
