(defun f(n)
  ;(declare (optimize (safety 0) (speed 3) (debug 0)))
  (declare (type fixnum n))
   (+ (+ (- (* 2 (* n n)) n) (- 1 (mod n 2))) 1))

(defun s(n)
  ;(declare (optimize (safety 0) (speed 3) (debug 0)))
  (declare (type fixnum n i sum))
  (loop for i from 1 upto n
	summing (f i) into sum
	finally (return (- sum 1))))

(compile 'f)
(compile 's)
(time (format 't "s(~D) = ~D~%" 1001 (s 1001)))

(loop for n from 1 upto 20 do(
	  if (= (mod n 2) 1) (format 't "s(~D) = ~D~%" n (s n))))

