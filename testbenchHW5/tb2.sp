TestBench2 for Homework5
* 2024 EDA course testbench netlist
* This circuit is from Page 22 of Lecture 6.

v1 ns 0  1
r1 ns a1 1
l1 a1 n1 1u
c1 n1 0  10p
r2 n1 a2 10
l2 a2 n2 2u
c2 n2 0  100p

.ac dec 10 1 1G
.plot ac v(n2)

.end
