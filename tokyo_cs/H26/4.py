import math
line = 3
part = 10 * 5 * math.sqrt(3) / 2

n = int(input('n: '))

area = part
for i in range(n):
    part = part / (3**2)    # each part
    area = area + part * line
    line = 4 * line
 
print('K({0}) = {1}'.format(n,area))
