netlist example

* this is a line of comment


Vin 1 0 1
l1 1 0 10m

.dc Vin 0 10 1
.plot dc V(1)
.ac dec 10 1 10000
.plot ac  V(1)

* Is 0 2 10

.end
