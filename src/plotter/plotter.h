#ifndef PLOTTER_H
#define PLOTTER_H


#include <QObject>
#include <QVector>

#include <vector>
#include "qcustomplot/qcustomplot.h"
extern QCustomPlot *custPlot;

using namespace std;

enum PlotType {
    LINEAR=0,
    DEC
};

void initPlot(QCustomPlot *plot);

void newPlotWindow(vector<double> xData, vector<double> yData, string xLabel, string yLabel, string title, PlotType plotType=LINEAR);

#endif