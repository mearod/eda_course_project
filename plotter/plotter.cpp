#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QTextStream>
#include <QVector>

#include <vector>

#include "qcustomplot/qcustomplot.h"
#include "plotter.h"

using namespace std;


void initPlot(QCustomPlot *plot)
{

}

void newPlotWindow(vector<double> xData, vector<double> yData, string xLabel, string yLabel, PlotType plotType)
{
    QString xQLabel, yQLabel;
    xQLabel = QString::fromStdString(xLabel);
    yQLabel = QString::fromStdString(yLabel);

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

    newPlot->xAxis->setLabel(xQLabel);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    newPlot->xAxis->setTicker(logTicker);
    if(plotType == LINEAR)
    {
        newPlot->xAxis->setScaleType(QCPAxis::stLinear);
    }
    else if(plotType == DEC)
    {
        newPlot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    }
    newPlot->yAxis->setLabel(yQLabel);

    newPlot->replot();
    newPlot->setMinimumSize(450, 300);

    newPlot->setAttribute(Qt::WA_DeleteOnClose);
    newPlot->show();
}


