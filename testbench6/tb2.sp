* Testbench 2 for homework 6

V1 n1 0 sin(0 1 1 0 0)
R1 n1 n2 10k
D1 n2 0  d

* for simulating with ngspice
*.model diode1 D
*.save tran v(n1)
*.save tran v(n2)

.tran 0.01 2 0
.plot tran v(n1)
.plot tran v(n2)

.end
