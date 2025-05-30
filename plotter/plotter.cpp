#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QTextStream>
#include <QVector>

#include <vector.h>

#include "qcustomplot/qcustomplot.h"
#include "plotter.h"

using namespace std;


void initPlot(QCustomPlot *plot)
{

}

void newPlotWindow(vector<double> xData, vector<double> yData, string xLabel, string yLabel, PlotType plotType=LINEAR);
{
    Qstring xLabel, yLabel;
    xLabel = QString::fromStdString(xLabelString);
    yLabel = QString::fromStdString(yLabelString);

    QVector<double> xQData, yQData;
    for(int i = 0; i < xData.size(); i++)
    {
        xQData.append(xData[i]);
        yQData.append(yData[i]);
    }

    QCustomPlot *newPlot = new QCustomPlot();
    newPlot->addGraph(newPlot->xAxis, newPlot->yAxis);
    newPlot->graph(0)->setPen(QPen(QPen(Qt::blue)));
    newPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    newPlot->graph(0)->setData(xQData, yQData);
    newPlot->graph(0)->rescaleAxes();

    custPlot->xAxis->setLabel(xlabel);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    custPlot->xAxis->setTicker(logTicker);
    if(plotType == LINEAR)
    {
        custPlot->xAxis->setScaleType(QCPAxis::stLinear);
    }
    else if(plotType == DEC)
    {
        custPlot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    }
    custPlot->yAxis->setLabel(yLabel);

    custPlot->replot();
    custPlot->setMinimumSize(450, 300);

    custPlot->setAttribute(Qt::WA_DeleteOnClose);
    custPlot->show();
}


