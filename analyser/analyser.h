#ifndef _ANALYSER_H_
#define _ANALYSER_H_
#include <armadillo>
#include "../circuit/circuit.h"
using namespace arma;

class Circuit;

class Analyser
{
private:
    void devicesStampDC();
    void devicesStampAC();
    void solveDC();
    void solveAC();
public:


    Circuit* circuit;
    int bTypeDeviceNum;
    int nodeNum;
    int bTypeDeviceCounter;//for branch matrix generate
    cx_mat mna;//mna Matrix
    cx_vec rhs;

    double freq;

public:
    Analyser(Circuit* circuit);
    ~Analyser();

    void analyseDC();
    void analyseAC();
};

#endif