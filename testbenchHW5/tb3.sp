Testbench1 for homework5
* This circuit is from Pgae 3 of Lecture 8.

Vs n1 0  0   pulse(0 0.5 1n 1n 1n 100n 200n)
R1 n1 n2 100
L1 n2 n3 1000n
C1 n3 0  10p

.tran 0.1n 400n 
.plot tran I(R1)
.plot tran V(n2)

.end
