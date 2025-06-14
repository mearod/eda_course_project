* Testbench 3 for homework 6

Vd nd 0 1
Mn nd ng ns 0 mosn L=1u W=2u
R1 ns 0 1
Vg ng 0 0.5

* for simulating with ngspice
*.model mosn nmos level=1
*.save dc v(ns)

.dc Vd 0 1 0.01
.plot dc v(ns)

.end
