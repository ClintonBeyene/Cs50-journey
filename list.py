
from cs50 import get_string

people = {
    "clinton": "0968798292",
    "Tadelech": "0916138748",
    "Beyene": "0937220207",
}

name = get_string("Name: ")


if name in people:
        print(f"Number: {people[name]}")

else:
     print("Not Found")

