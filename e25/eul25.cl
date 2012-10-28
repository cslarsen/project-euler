; projecteuler.net problem 25

(defun fibnext(n l r)
  (if (= n 1)
    (+ l r)
    (fibnext (- n 1) r (+ l r))))

(defun fib(n)
  "Return nth number in Fibonacci sequence"
  (if (< n 3)
    1
    (fibnext (- n 2) 1 1)))

(defun fibiter(nth)
  "Return nth number in Fibonacci sequence"
  (do ((n 0 (1+ n))
       (cur 0 next)
       (next 1 (+ cur next)))
      ((= nth n) cur)))


;(loop for n from 1 upto 100 do(
;	format 't "fib(~D) = ~D has ~D digits~%" n (fib n) (length (write-to-string (fib n)))))

(setf digits 0)
(setf n 1)
(loop (< digits 10)
       (setf n (+ n 1))
	(setf digits (fib n)))
(format 't "F~D contains 10 digits~%" n)

