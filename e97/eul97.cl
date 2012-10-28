(defun eul97()
  (declare (optimize (safety 0) (speed 3) (debug 0)))
  (print (+ (expt 2 7830457) 1)))

(compile 'eul97)
(eul97)
