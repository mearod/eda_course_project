netlist example

* this is a line of comment


Vin 1 0 1
c1 1 2 1m
R1 2 0 1
R2 2 3 1
c2 3 0 1u

.ac dec 10 0.1 1G
.plot ac  I(c1)

.tran 100u
.plot tran I(c1)

* Is 0 2 10

.end
