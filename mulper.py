
import sys
from functools import reduce
from itertools import product


def multiplication_persistence(num, verbose=False):
    if verbose:
        print(n)

    if num < 10:
        return 0

    product = 1
    n = num
    while n > 0:
        product *= (n % 10)
        n //= 10
    return 1 + multiplication_persistence(product, verbose)

def loop(count, start=1):
    best = 0
    for num in range(start + 1, start + count + 1):
        iters = multiplication_persistence(num)
        if iters > best:
            best = iters
        print('{num}\t ITR: {iters} BEST: {best}'.format(num=num, iters=iters, best=best))

def smart_search(digits):
    search_len = ((digits + 1) * (digits + 2)) // 2
    count = 0

    for i in range(digits, -1, -1):
        for k in range(digits - i + 1):
            j = digits - (i + k)
            num = int('2' * i + '3' * j + '7' * k)
            print(num, '\t', multiplication_persistence(num))

            count += 1
            print('{} of {}'.format(count, search_len))



def main():
    # if len(sys.argv) == 1:
    #     count = 10000
    #     start = 1
    # elif len(sys.argv) == 2:
    #     count = int(sys.argv[1])
    #     start = 1
    # else:
    #     count = int(sys.argv[1])
    #     start = int(sys.argv[2])

    # loop(count, start)
    if len(sys.argv) == 1:
        digits = 20
    else:
        digits = int(sys.argv[1])

    smart_search(digits)

if __name__ == '__main__':
    main()

