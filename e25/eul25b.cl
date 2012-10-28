; projecteuler.net problem 25

(defun fibdig(digits)
  "Return n for which F(n) that has more than 'digits numbers"
  (do ((n 0 (1+ n))
       (cur 0 next)
       (next 1 (+ cur next)))
    ( (= (length (write-to-string cur)) digits) n)))

(compile 'fibdig)
(format 't "F(~D) contains 1000 digits~%" (fibdig 1000))
