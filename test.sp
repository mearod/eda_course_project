netlist example

* this is a line of comment


Vin n2 0 1
R1 n2 n1 1
R2 n1 0 1

.dc Vin
.plot dc V(2)

* Is 0 2 10

.end
