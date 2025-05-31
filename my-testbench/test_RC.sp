netlist example

* this is a line of comment


Vin 3 0 1
R1 3 2 200m
C1 2 1 100m
L1 1 0 100m

.ac dec 10 1 1000000000
.plot ac V(2)
.tran 4
.plot tran  V(2)

* Is 0 2 10

.end
