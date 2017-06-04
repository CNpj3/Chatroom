import csv

f = open('example.csv', 'r')  
for row in csv.reader(f):  
    print row  
f.close()  
