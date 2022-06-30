#!/bin/bash

./scc < bigdata.s | ./simplesim > out
./scc_check < bigdata.s | ./simplesim_check > key
echo "bigdata.s:"
diff out key

./scc < bigpgm.s | ./simplesim > out
./scc_check < bigpgm.s | ./simplesim_check > key
echo "bigpgm.s:"
diff out key

./scc < bigpgmvar.s | ./simplesim > out
./scc_check < bigpgmvar.s | ./simplesim_check > key
echo "bigpgmvar.s:"
diff out key

./scc < bigpgmcmd.s | ./simplesim > out
./scc_check < bigpgmcmd.s | ./simplesim_check > key
echo "bigpgmcmd.s:"
diff out key

./scc < bigpgmstack.s | ./simplesim > out
./scc_check < bigpgmstack.s | ./simplesim_check > key
echo "bigpgmstack.s:"
diff out key

./scc < end.s | ./simplesim > out
./scc_check < end.s | ./simplesim_check > key
echo "end.s:"
diff out key

./scc < read.s | ./simplesim > out
./scc_check < read.s | ./simplesim_check > key
echo "read.s:"
diff out key

./scc < rw.s | ./simplesim > out
./scc_check < rw.s | ./simplesim_check > key
echo "rw.s: "
diff out key

./scc < max.s | ./simplesim > out
./scc_check < max.s | ./simplesim_check > key
echo "max.s: "
diff out key

./scc < if_c_eq_c.s | ./simplesim > out
./scc_check < if_c_eq_c.s | ./simplesim_check > key
echo "if_c_eq_c.s: "
diff out key

./scc < if_c_ge_c.s | ./simplesim > out
./scc_check < if_c_ge_c.s | ./simplesim_check > key
echo "if_c_ge_c.s: "
diff out key

./scc < if_c_gt_c.s | ./simplesim > out
./scc_check < if_c_gt_c.s | ./simplesim_check > key
echo "if_c_gt_c.s: "
diff out key

./scc < if_c_le_c.s | ./simplesim > out
./scc_check < if_c_le_c.s | ./simplesim_check > key
echo "if_c_le_c.s: "
diff out key

./scc < if_c_lt_c.s | ./simplesim > out
./scc_check < if_c_lt_c.s | ./simplesim_check > key
echo "if_c_lt_c.s: "
diff out key

./scc < if_c_ne_c.s | ./simplesim > out
./scc_check < if_c_ne_c.s | ./simplesim_check > key
echo "if_c_ne_c.s: "
diff out key

./scc < if_v_eq_v.s | ./simplesim > out
./scc_check < if_v_eq_v.s | ./simplesim_check > key
echo "if_v_eq_v.s: "
diff out key

./scc < if_v_ne_v.s | ./simplesim > out
./scc_check < if_v_ne_v.s | ./simplesim_check > key
echo "if_v_ne_v.s: "
diff out key

./scc < sum.s | ./simplesim > out
./scc_check <sum.s | ./simplesim_check > key
echo "sum.s: "
diff out key

./scc < prime.s | ./simplesim > out
./scc_check < prime.s | ./simplesim_check > key
echo "prime.s: "
diff out key

echo "end"
