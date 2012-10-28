(setf *sum* 0)
(defun fib (N)
	(if (or (= n 0) (= n 1) )
		1
	((setf a (fib (- n 1)))
	 (setf b (fib (- n 2)))
	 (if (= (mod a 2) 0) (setf *sum* (+ *sum* a)))
	 (if (= (mod b 2) 0) (setf *sum* (+ *sum* b)))
	 (+ (fib (- n 1)) (fib (- n 2))))))
	 
(print (fib 10))
(print *sum*)
