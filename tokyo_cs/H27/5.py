#from __future__ import print_function

def diff(line1, line2):
    length = max(len(line1), len(line2))
    newline1 = line1 + ' ' * (length - len(line1))
    newline2 = line2 + ' ' * (length - len(line2))
    count = 0
    for i in range(length):
        if (newline1[i] != newline2[i]):
            count += 1
    return count


f = open("program.txt")
lines = f.read().split('\n')
validLine = []

for line in lines:
    if (len(line) >= 20 and line not in validLine):
        vaildLine.append(line)

row = len(validLine)
for i in range(row):
    for j in range(i+1,row):
        d = diff(validLine[i], validLine[j])
        if (d < 5 and d != 0):
            # print (validLine[i], validLine[j], sep=',')
            print (validLine[i], validLine[j])
