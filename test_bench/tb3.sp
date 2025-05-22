Testbench 3 for homework 4
* The circuit is from Page 15 in Lecture 6.

R1 n1 0 1
G2 n1 0 n1 n2 1
R3 n1 n2 2
R4 n2 0 5
Is5 0 n2 1
Vs6 n3 n2 dc 1
E7 n4 0 n1 n2 1
R8 n3 n4 10

.dc Vs6 1 1 1
.print dc v(n2)

.end
