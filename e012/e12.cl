(defun tri (n)
	"compute triangle number"
	(if (= n 1) 1 (+ n (tri (- n 1)))))

(defun divisors (n)
	"print divisors of n"
	(loop for i from 1 upto n do(
		when (= (mod n i) 0) (format 't "~D " i))))

(defun numdivs (n)
	"count divisors of n"
	(setf ret 0)
	(loop for i from 1 upto n do(
		when (= (mod n i) 0) (setf ret (+ ret 1))))
	ret)

(defun eul12 ()
	"projecteuler.net problem 12"
	(loop for n from 1 upto 10000000 do(if (> (numdivs (tri n)) 500)  (format 't "~D has ~D divisors~%" (tri n) (numdivs (tri n))(setf n 99999999)))))
;	(loop for n from 1 upto 10000000 do(format 't "~D has ~D divisors~%" (tri n) (numdivs (tri n)))))

(print "start")
(compile 'numdivs)
(compile 'tri)
(compile 'divisors)
(compile 'eul12)
(eul12)
