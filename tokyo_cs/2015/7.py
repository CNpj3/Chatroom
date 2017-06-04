import math

def englishToInteger(eng):
    return {
        'zero':         0,
        'one':          1,
        'two':          2,
        'three':        3,
        'four':         4,
        'five':         5,
        'six':          6,
        'seven':        7,
        'eight':        8,
        'nine':         9,
        'ten':          10,
        'eleven':       11,
        'twelve':       12,
        'thirteen':     13,
        'fourteen':     14,
        'fiveteen':     15,
        'sixteen':      16,
        'seventeen':    17,
        'eighteen':     18,
        'nineteen':     19,
        'twenty':       20,
        'thirty':       30,
        'forty':        40,
        'fifty':        50,
        'sixty':        60,
        'seventy':      70,
        'eighty':       80,
        'ninty':        90,
        'hundred':      100,
        'thousand':     1000,
    }[eng]

expression = raw_input('Please input English expression: ')
print(expression)
expression = expression.split()
length = len(expression)
result = 0
tmp=0

if length<=1:
    print("Decimal: {}".format(englishToInteger(expression[0])))
else:
    for i in range(0,length):
        # print(expression[i])
        number = englishToInteger(expression[i])
        if number==100 or number==1000:
            if i!=0:
                tmp*=number
                result+=tmp
                tmp=0
        else:
            tmp+=number
    result+=tmp
    print("Decimal: {}".format(result))
