Testbench 2 for homework 4
* The circuit is from Page 9 in Lecture 6.

R1 1 0 5
G2 1 0 1 2 2
R3 1 2 6
R4 2 0 8
Is 0 2 10

.dc Is 10 10 1
.print dc v(2)

.options node list

.end
