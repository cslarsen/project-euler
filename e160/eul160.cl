(defun fac(n)
	(if (= n 1) 1 (* n (fac (- n 1)))))

(compile 'fac)
(print (fac 1000000000000))
