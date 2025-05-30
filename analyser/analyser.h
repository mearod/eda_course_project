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
    void matrixNodeRecordDC(double scanValue,ResultRecorder* resultRecorder);
    void matrixNodeRecordAC(double scanValue,ResultRecorder* resultRecorder);
    bool checkPlotNodeExists();
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

//tran analysis
    double tranTime;
    double tranStep;

public:
    Analyser(Circuit* circuit);
    ~Analyser();

    void analyseDC();
    void analyseAC();
    void analyseTRAN();

    void analyseStepDC();
    void analyseStepAC();
    void analyseStepTRAN();

    void createSingleRecord();
    void stepRecord();
};

#endif