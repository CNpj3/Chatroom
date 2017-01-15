import math     # power

BASE = 4

input = raw_input('Please input {}-base representation: '.format(BASE)) 
length = len(input)
sum=0
for i in range(0,length):
    power=length-i-1
    sum+=int(math.pow(BASE,power)) * int(input[i])
print('decimial representation: {}'.format(sum))
