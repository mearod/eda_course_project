Testbench 4 for homework 5

* This circuit is from Page 27 of Lecuture 8.

Vin n1 0 sin(0 1 100mEg 0 1e8)

R1 n1 n2 10
L1 n1 n2 1u
C2 n2 0  100p

.tran 1n 60n
.plot tran v(n2)

.end
