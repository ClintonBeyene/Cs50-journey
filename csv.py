
import csv

file = open("phonebook.csv", "a")

name = input("Name: ")
number = input("Number: ")

writter = csv.writter(file)
writer.writerow([name, number])

file(close)
