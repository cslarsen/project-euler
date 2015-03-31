problem_63 = length . concatMap (takeWhile (\(n,p) -> n == nDigits p))
             $ [powers d | d <- [1..9]]
    where powers d = [(n, d^n) | n <- [1..]]
          nDigits n = length (show n)

