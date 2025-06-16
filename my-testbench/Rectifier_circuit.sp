* Testbench 2 for homework 6

V1 pos 0 sin(0 10 1 0 0)
R1 1 2 1k
C1 1 2 10m
D1 pos 1  d
D2 0 1 d
D3 2 pos d
D4 2 0 d

* for simulating with ngspice
*.model diode1 D
*.save tran v(n1)
*.save tran v(n2)

.tran 0.01 2 0
.plot tran v(1)
.plot tran V(2)
.plot tran I(R1)
.plot tran I(V1)


.end