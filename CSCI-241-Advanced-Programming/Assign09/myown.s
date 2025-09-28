20  input x
30  data 100
42  rem
50  if x < 2 goto 160
63  rem
70  let h = x/2
80  let d = 2
90  rem
100 if d > h goto 190
120 let y = d*(x / d)
130 if x == y goto 160
140 let d = d + 1
150 goto 90
160 rem
161 rem   x is not prime
162 rem 
170 print -1 
180 end
190 rem 
191 rem   x is prime
192 rem
200 print 1 
210 end
