Testbench1 for homework 5
* resistive ladder

R03 0  n3 3k
R23 n2 n3 1k
R02 0  n2 2k
R12 n1 n2 1k
R01 0  n1 2k
Vin n3 0  dc 5

.op

.dc Vin 0 15 0.5
.plot dc v(n1)

.end

