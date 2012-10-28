(defun gaussian-integerp (z)
  (declare (optimize (safety 0) (speed 3) (debug 0)))
  (assert (numberp z))
  (and (integerp (realpart z)) (integerp (imagpart z))))

(defun gausdiv(n)
  (declare (optimize (safety 0) (speed 3) (debug 0)))
  (declare (type fixnum a b n))
  (setf sum (complex 0 0))
  (loop for a from 1 to n do 
    (loop for b from (- 0 n) to n do
      (if (gaussian-integerp (/ n (complex a b)))
        (setf sum (+ sum (complex a b))))))
  sum)

(defun eul153()
  (declare (optimize (safety 0) (speed 3) (debug 0)))
  (declare (type fixnum n))
  (declare (type complex sum gd))
  (setf sum (complex 0 0))
  (print sum)
  (loop for n from 1 to 100000 do
	(setf gd (gausdiv n))
	(setf sum (+ gd sum))
	(print sum)
	(format 't "n=~D, gd=~D, sum=~D~%" n gd sum))
  (print sum))

(compile 'gaussian-integerp)
(compile 'gausdiv)
(compile 'eul153)
(time (eul153))
