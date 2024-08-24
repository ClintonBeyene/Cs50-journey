from cs50 import get_string

s = get_string("do you agree? ").lower()

if s in ["y", "yes"]:
    print("agreed")
elif s in ["n", "no"]:
    print("not agreed")


