(defun fibonacci (N)
  "Compute the N'th Fibonacci number."
  (if (or (zerop N) (= N 1))
      1
    (+ (fibonacci (- N 1)) (fibonacci (- N 2)))))

(print (fibonacci 10))
