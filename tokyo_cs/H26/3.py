import math
line = 3
part = 10 * 5 * math.sqrt(3) / 2

area = part
for i in range(2):
    part = part / (3**2)    # each part
    area = area + part * line
    line = 4 * line
 
print('K(2) = {}'.format(area))
