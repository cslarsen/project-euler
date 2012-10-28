
(defun route (x y N)
	(if (and (= x N) (= y N))
		1
		(+ (if (< x N) (route (+ x 1) y N) 0)
		   (if (< y N) (route x (+ y 1) N) 0))))
(defun eul15 ()
	(loop for n from 1 upto 20 do(format 't "~Dx~D grid has ~D routes~%" n n (route 0 0 n))))

(compile 'route)
(compile 'eul15)
(eul15)
