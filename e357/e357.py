primes = set()

def divisors(n):
    for i in xrange(1,1+n):
        if (n % i) == 0:
            yield i

def isprime(n):
    if n in primes:
        return True

    for d in xrange(2,n):
        if (n % d) == 0:
            return False

    primes.update([n])
    return True

def primediv(n):
    if not isprime(n+1):
        return False
    for d in divisors(n):
        if not isprime(d + n//d):
            return False
    return True

def main():
    assert(list(divisors(30)) == [1,2,3,5,6,10,15,30])
    assert(primediv(30))
    assert(not primediv(31))
    assert(not primediv(29))
    for n in [1,2,6,10,22,30,42,58,70,78,82]:
        assert(primediv(n))

    s = 0
    for n in xrange(1,200):
        if primediv(n):
            s += n
            print(n,s)

if __name__ == "__main__":
    main()
    print("")
