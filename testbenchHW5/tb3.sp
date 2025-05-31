Testbench1 for homework5
* This circuit is from Pgae 3 of Lecture 8.

Vs n1 0  0   pulse(0 1 2n 2n 2n 50n 100n)
R1 n1 n2 100
C1 n2 0  10p

.tran 0.1n 200n 
.plot tran V(n2)

.end
