#!/bin/bash
echo "t1"
./josephus > out.me
diff --color out.me josephus.refout

echo "t2"
./josephus -n 10000 -p 1000 -c 20 > out.me
diff --color out.me josephus.refout-n10000-p1000-c20

echo "t3"
./josephus -n 1000 -p 104 > out.me
diff --color out.me josephus.refout-n1000-p104

echo "t3"
./josephus -n 25 > out.me
diff --color out.me josephus.refout-n25

echo "t4"
./josephus -n 25 -m 2 > out.me
diff --color out.me josephus.refout-n25-m2

echo "t5"
./josephus -n 25 -m 2 -p 1 > out.me
diff --color out.me josephus.refout-n25-m2-p1

echo "t6"
./josephus -n 25 -m 2 -p 1 -c 30 > out.me
diff --color out.me josephus.refout-n25-m2-p1-c30

echo "t7"
./josephus -n 676 -p 100 > out.me
diff --color out.me josephus.refout-n676-p100

echo "t8"
./josephus -n 677 -p 100 > out.me
diff --color out.me josephus.refout-n677-p100

echo "t9"
./josephus -n 97 -m 23 -p 11 > out.me
diff --color out.me josephus.refout-n97-m23-p11

echo "END"
