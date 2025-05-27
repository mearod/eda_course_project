#ifndef _ANALYSER_H_
#define _ANALYSER_H_
#include <armadillo>
#include "../devices/device.h"
#include "../circuit/circuit.h"
#include "../result_recorder/result_recorder.h"
using namespace arma;

class Circuit;

class ResultRecorder;

class Analyser
{
private:
    void devicesStampDC();
    void devicesStampAC();
    void solveDC();
    void solveAC();
    void matrixNodeRecord(double scanValue,ResultRecorder* resultRecorder);
public:

    ResultRecorder* resultRecorderDC;
    ResultRecorder* resultRecorderAC;
    ResultRecorder* resultRecorderTRAN;

    Circuit* circuit;
    int bTypeDeviceNum;
    int nodeNum;
    int bTypeDeviceCounter;//for branch matrix generate
    cx_mat mna;//mna Matrix
    cx_vec rhs;
    cx_vec x;
    double freq;

public:
    Analyser(Circuit* circuit);
    ~Analyser();

    void analyseDC(string scannedDevice, double start,double end,double step);
    void analyseAC(int denseNum,double start,double end);
    void analyseTRAN(double start,double end,double step);

    void analyseStepDC();
    void analyseStepAC();

    void createSingleRecord();
    void stepRecord();
};

#endif