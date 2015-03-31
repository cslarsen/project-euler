; projecteuler.net problem 29

(defun myget()
  (declare (type fixnum a b))
  (loop for a from 2 to 100 do
    (loop for b from 2 to 100 do
      (print (expt a b)))))

(compile 'myget)
(print (myget))
; clisp eul29.cl | sort | uniq | wc -l = 9184, ans is 9183
