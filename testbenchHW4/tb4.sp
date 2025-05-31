TestBench4 for Homework4
* 2024 EDA course testbench netlist

r2 2 1 2
v2 0 1 dc 1 ac 10
l1 0 2 10
r1 1 3 1
c2 3 2 2

.ac dec 10 1 1g
.plot ac v(2)
.end
