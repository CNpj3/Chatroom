f = open("program.txt")
lines = f.read().split()

printLines = []

for i in range(len(lines)):
    if (lines[i] in printLines)
        continue
    for j in range(i+1, len(lines)):
        d = 0
        while j+d < len(lines) and lines[i+d]==lines[j+d]:
            d += 1
        t = '\n'.join(lines[i:i+d])
        if d>=4 and 
