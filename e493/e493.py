#! /usr/bin/env python

import decimal
import random

def counts(sample):
    return len(set(sample))

def make(colors=7, quantity=10):
    urn = range(colors)*quantity
    return urn

def sample(urn, take=20):
    urn = urn[:]
    random.shuffle(urn)
    return urn[:take]

def avg(lst):
    return float(sum(lst))/len(lst)

def approximate(iterations=100):
    sum = 0
    len = 0
    for n in range(iterations):
        sum += counts(sample(make()))
        len += 1
    return float(sum) / len

def running_avg():
    sum = 0
    len = 0
    while True:
        urn = range(1,8)*10
        random.shuffle(urn)
        for offset in range(70-20):
            sample = urn[offset:20+offset]
            sum += counts(sample)
            len += 1
        ratio = decimal.Decimal(sum) / decimal.Decimal(len)
        print("%d %d %s" % (len, sum, ratio))

if __name__ == "__main__":
    decimal.setcontext(decimal.Context(prec=20))
    running_avg()
