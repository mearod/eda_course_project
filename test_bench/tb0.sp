TestBench0 for Homework4 - Stamp Example
* 2024 EDA course testbench netlist

Vin 1 0 3
R1 1 2 200
R2 2 0 100

.dc Vin 1 10 0.1
.plot dc V(1) V(2) 
.end

**********************************
* MNA Matrix (including ground)
*
*   [ 0.01   0.    -0.01 ]
*   [ 0.     0.005 -0.005]
*   [-0.01  -0.005  0.015]
*
*       RHS Vector
*           [0.]
*           [0.]
*           [0.]

**********************************
* MNA Matrix (excluding ground)
*
*   [0.005  -0.005]
*   [-0.005  0.015]
*
*       RHS Vector
*           [0.]
*           [0.]
