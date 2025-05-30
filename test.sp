netlist example

* this is a line of comment


Vin n2 0 1
R1 n1 0 1
c2 n2 n1 1m

.dc Vin
.plot dc V(2)

* Is 0 2 10

.end
