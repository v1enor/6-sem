import random

def lcg(seed, count):
    a = 421
    c = 1663
    n = 7875
    x = seed
    result = []
    for i in range(count):
        x = (a * x + c) % n
        rand_num = x / float(n)
        result.append(rand_num)
    return result

random_numbers = lcg(123, 10)
print(random_numbers)
