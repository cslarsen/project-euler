(defun primep (x)
  "Predicate to test the primality of x."
  (let ((sqrt-x (sqrt x)))
    (do ((i 2 (1+ i)))
        ((> i sqrt-x) t)
      (when (eq (mod x i) 0)
        (return nil)))))

(loop for i from 1 upto (sqrt 317584931803) do(
        if (and (primep i) (= (mod 317584931803 i) 0)) (print i))
)
