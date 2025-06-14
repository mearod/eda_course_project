* Testbench 1 for homework 6

V1 n1 0 1
D1 n1 n2 d
V2 n2 0 0

* for simulating with ngspice
*.model diode1 D
*.save dc i(V2)

.dc V1 0 1 0.01
.plot dc i(V2)

.end
