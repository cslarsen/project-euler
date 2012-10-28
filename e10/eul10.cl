(defun primep (x)
  "Predicate to test the primality of x."
  (let ((sqrt-x (sqrt x)))
    (do ((i 2 (1+ i)))
        ((> i sqrt-x) t)
      (when (eq (mod x i) 0)
	(return nil)))))

(defun main (args)
  "projecteuler.net problem 10" args
	(let ((sum 0) (upper 1000000))
	(loop for n from 2 upto upper do
		(when (primep n)
			(setf sum (+ sum n))))
	(format 't "~%sum is ~D for primes below ~D~%" sum upper)))
(compile 'primep)
(compile 'main)
(main "")


