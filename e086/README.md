ProjectEuler Problem 86
-----------------------

Imagine a line from fly to the two spiders. So to routes there, and one via the
roof. For each combination of integers l,h,w < m, we want to find the shortest
of the three routes, and if it's an integer, count it.

For m=100, there are 2060 such (distinct) cuboids.
For m=99, the solution is 1975.

Strategy
--------

The shortest route between two points is a straight line, so we'll flatten the
cuboid:

     Cuboid = L*W*H
     x = spider
     f = fly
                           L
                      +---------x
                      |         |
                    H |         |
                      |         |
                +-----+---------+-----x
                |     |         |     |
              W |     | bottom  |     | W
           L    |     |         |     |
      +---------+-----f---------+-----+
      |         |  H  |         |  H
    W |   top   |     |         |
      |         |     |         |
      x---------+     +---------+

From this we can see that there are three distinct routes:

    * sqrt((L+H)^2 + W^2)
    * sqrt((W+H)^2 + L^2)
    * H + sqrt(L^2 + W^2)

The code for this is in `e86.py`, and it seems to work fine for the two cases.
Now comes the interesting part; how to make it fast.

Optimization ideas
------------------

    * It seems we can use dynamic programming, building on previous solutions.
      When we've found the solution for `M(99)` it's just one other step to
      calculate `M(100)`, so we should have `M(n+1) = M(0) + M(n)` and `M(0) = 0`.

    * We want to find out if `sqrt((a+b)**2 + c**2)` is integer. There are
      probably some tricks here. In worst case, we could create a lookup table
      and just check out if `(a+b)**2 + c**2` is in that set.

I think that should be enough for now.
