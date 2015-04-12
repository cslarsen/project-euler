# Project Euler problem 387
# Solved by Christian Stigen Larsen

import math

def digitsum(n):
    s = 0
    while n:
        s += n % 10
        n //= 10
    return s

def harshad(n):
    return (n % digitsum(n)) == 0

def isprime(n):
    if n<=1:
        return False

    for d in xrange(2, 1+int(math.sqrt(n))):
        if (n % d) == 0:
            return False

    return True

def strong_harshad(n):
    """Strong Harshad."""
    if n <= 1:
        return False
    else:
        return isprime(n // digitsum(n))

def rt_harshad(n):
    """Right-truncatable Harshad number."""
    while n > 1:
        if not harshad(n):
            return False
        n //= 10
    return True

def strong_rt_harshad(n):
    if not isprime(n):
        return False
    n //= 10
    return strong_harshad(n) and rt_harshad(n)

def srt_sum(limit):
    s = 0
    for n in xrange(limit):
        if strong_rt_harshad(n):
            s += n
    return s

def srtf_sum(limit):
    """Fast version of srt_sum."""
    return srt_sum(limit) # not implemented yet

def main():
    print(srtf_sum(1000))

def test():
    assert(not isprime(1))
    assert(isprime(2))
    assert(isprime(71))
    assert(harshad(2))
    assert(digitsum(2) == 2)
    assert(digitsum(123) == 1+2+3)
    assert(harshad(201))
    assert(not harshad(202))
    assert(rt_harshad(201))
    assert(strong_harshad(201))
    assert(not strong_harshad(202))
    assert(strong_rt_harshad(2011))
    assert(not strong_rt_harshad(2012))
    assert(srt_sum(10000) == 90619)

if __name__ == "__main__":
    test()
    main()
