import math     # power

BASE = 7

# switch by dictionary
def toInteger(x):
    return {
        'a': 0,
        'b': 1,
        'c': 2,
        'd': 3,
        'e': 4,
        'f': 5,
        'g': 6,
    }[x]

input = raw_input('Please input {}-base representation: '.format(BASE)) 
length = len(input)
sum=0
for i in range(0,length):
    # print(toInteger(input[i]))
    power=length-i-1
    sum+=int(math.pow(BASE,power)) * toInteger(input[i])
print('decimial representation: {}'.format(sum))
