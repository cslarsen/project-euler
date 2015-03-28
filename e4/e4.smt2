;; Project Euler problem 4
;; Inspired by http://blogs.teamb.com/craigstuntz/2014/07/07/38818/
;;
;; Usage: z3 -smt2 e4.smt2
;;
;; Written by Christian Stigen Larsen

(set-option :print-success false)
(set-option :smtlib2_compliant true)
(set-option :verbose 10)

(declare-const a Int)
(declare-const b Int)
(declare-const c Int)
(declare-const p Int)
(declare-const q Int)
(declare-const pq Int)

(assert
 (and
  (<= 1 a 9)
  (<= 0 b 9)
  (<= 0 c 9)

  (<= 100 p 999)
  (<= p q 999)

  (= pq
     (* p q)
     (+ (* a 100000)
        (* b 10000)
        (* c 1000)
        (* c 100)
        (* b 10)
        (* a 1)))))

;(maximize pq)

(check-sat)
(get-model)
