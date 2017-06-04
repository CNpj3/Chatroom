import math

d = float(input('Set d:'))
n = math.floor(10.0/abs(d)) + 1

ans = 0
for p in range(math.ceil(10/d)+1):      # only python3, use for float range point
    for q in range(math.ceil(10/d)+1):
        if ((d*p - 5)**2 + (d*q - 5)**2 <= 5**2):
            ans += 1
a = ans / n**2 / 4
print(a)
