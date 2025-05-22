TestBench0 for Homework4 - Stamp Example
* 2024 EDA course testbench netlist

V1 2 0 2
R1 2 1 100
R2 1 0 200
R3 1 0 200


.op
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



