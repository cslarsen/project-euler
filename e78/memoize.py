"""
Implementation of memoization decorator in Python.

Written by Christian Stigen Larsen
http://csl.sublevel3.org

Put in the public domain by the author, 2012

This is an example of how to use decorators to implement different kind of
behaviour in Python.

It is usable, but the intention is to show how it can be done.

Basically, you should only use memoization for referentially transparent
functions, i.e., functions that always return the same output for the same
input (they are also called _pure_ functions).

Since this is so simple, I urge you to extend this decorator for some cool
uses.  For instance, you could stick a timeout parameter in the memoization
decorator, making it safe to use it for impure functions.  For instance, for
web apps, you could save a lot by not hitting the database for each and
every function call.  Just stick a @memoize(timeout=timedelta(minutes=5)) or
something like that.

Example of cool uses:

  - Create a decorator that stores the data in a distributed redis or
    memcached setup.  Let several clients use the same data.  So ONE client
    does the grunt work, while the other reuse the output.

  - Add a timeout parameter to the decorator so that you can use the
    decorator for impure functions as well.

I think a lot of web environments use this idea.  I know for a fact that
Paul Graham's Arc Lisp does it via defmemo, but I'm not sure exactly how he
stores the data -- e.g. in an alist or a fast hash table?
"""

class memoize:
  """Decorator for adding memoization to functions.

  Just stick @memoize in front of function definitions,
  and you're good to go.
  """
  def __init__(self, function):
    self.function = function
    self.store = {}

  def __call__(self, *args):
    key = (args)

    # call function to store value
    if not key in self.store:
      self.store[key] = self.function(*args)

    # return stored value
    return self.store[key]

# show example usage
if __name__ == "__main__":
  import cProfile

  def fib_slow(n):
    "Returns the nth Fibonacci number (slow, non-memoized version)"
    if n == 0: return 0
    if n == 1: return 1
    return fib_slow(n-2) + fib_slow(n-1)

  @memoize
  def fib_fast(n):
    "Returns the nth Fibonacci number (fast, memoized version)"
    if n == 0: return 0
    if n == 1: return 1
    return fib_fast(n-2) + fib_fast(n-1)

  print "We're now going to run two versions of the same function."
  print "Both calculate the 35th Fibonacci number."
  print ""
  print "The first function is not memoized, and thus very slow."
  print "The second is memoized, using our decorator, and thus very fast."
  print ""
  print "Check out the speed differences between the two."
  print ""

  print "Calling fib_slow(35) ..."
  cProfile.run("fib_slow(35)")

  print "Calling fib_fast(35) ..."
  cProfile.run("fib_fast(35)")
