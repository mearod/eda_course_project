* Testbench 4 for homework 6

* inverter

Vin ng 0 pulse(0 1 1n 1n 1n 2n 5n)
Vdd n1 0 1

Mp nd ng n1 n1 mosp L=1u W=40u
Mn nd ng 0  0  mosn L=1u W=20u
C1 nd 0 0.01p

* for simulating with ngspice
*.model mosn nmos level=1
*.model mosp pmos level=1
*.save tran v(ng)
*.save tran v(nd)

.tran 1p 10n
.plot tran v(ng)
.plot tran v(nd)

.end
