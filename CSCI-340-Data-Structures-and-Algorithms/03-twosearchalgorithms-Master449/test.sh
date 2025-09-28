#!/bin/bash
echo "t1"
./twosearch > out.me
diff --color out.me twosearch.out

echo "t2"
./twosearch -w3 > out.me
diff --color out.me twosearch-w3.out

echo "t3"
./twosearch -l2 -h1002 > out.me
diff --color out.me twosearch-l2-h1002.out

echo "t3"
./twosearch -b 18 -c 9 > out.me
diff --color out.me twosearch-b18-c19.out

echo "t4"
./twosearch -a250 -b99 -c14 -h1234 -l21 -w5 -x9 -y7 > out.me
diff --color out.me twosearch-a250-b99-c14-h1234-l21-w5-x9-y7.out

echo "t5"
./twosearch -x &> out.me
diff --color out.me twosearch-x.out

echo "END"
