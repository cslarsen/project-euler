; projecteuler.net problem 25

(defun fibdig(digits)
  "Return n for which F(n) that has more than 'digits numbers"

   (declare (optimize (safety 0) (speed 3) (debug 0)
		        #+sbcl (sb-ext:inhibit-warnings 3)
			#+cmu (ext:inhibit-warnings 3)))

  (declare (type fixnum n cur maxnum digits next))
  (let ((maxnum (expt 10 (- digits 1))))
   (do ((n 0 (1+ n))
        (cur 0 next)
        (next 1 (+ cur next)))
     ((>= cur maxnum) n))))

(format 't "F(~D) contains 1000 digits~%" (fibdig 1000))
