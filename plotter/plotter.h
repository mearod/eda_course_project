#ifndef PLOTTER_H
#define PLOTTER_H


#include <QObject>
#include <QVector>

#include <vector>
#include "qcustomplot/qcustomplot.h"
#include "../result_recorder/result_recorder.h"
extern QCustomPlot *custPlot;
class SingleRecord;
using namespace std;
enum PlotType {
    LINEAR=0,
    DEC
};

void initPlot(QCustomPlot *plot);

void newPlotWindow(vector<double> xData, vector<double> yData, string xLabel, string yLabel, PlotType plotType=LINEAR);

#endif