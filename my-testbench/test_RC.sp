netlist example

* this is a line of comment


Vin 2 0  -2
R2 2 1 1
D2 1 0  model

.op
.dc Vin -2 0 0.01
.plot dc V(1) I(D2)


* Is 0 2 10

.end
