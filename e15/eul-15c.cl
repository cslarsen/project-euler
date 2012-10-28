(defun fac(n)
  (if (= n 1)
    1
    (* n (fac (- n 1)))))

(defun binom(n k)
  (/ (fac n)
       (* (fac k) (fac (- n k)))))

(defun route (n)
	(binom (* 2 n) n))

(defun eul15 ()
  	"projecteuler.net problem 15"
	(loop for n from 1 upto 20 do(format 't "~Dx~D grid has ~D routes~%" n n (route n))))

(eul15)
