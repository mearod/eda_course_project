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

void newPlotWindow(vector<double> xData, vector<double> yData, string xLabel, string yLabel, string title, PlotType plotType)
{
    QString xQLabel, yQLabel, titleQ;
    xQLabel = QString::fromStdString(xLabel);
    yQLabel = QString::fromStdString(yLabel);
    titleQ = QString::fromStdString(title);


    QVector<double> xQData, yQData;
    for(int i = 0; i < xData.size(); i++)
    {
        xQData.append(xData[i]);
        yQData.append(yData[i]);
    }

    QCustomPlot *newPlot = new QCustomPlot();
    
    QCPTextElement *titleText = new QCPTextElement(newPlot, titleQ, QFont("sans", 12, QFont::Bold));
    newPlot->plotLayout()->insertRow(0);
    newPlot->plotLayout()->addElement(0, 0, titleText);


    newPlot->addGraph(newPlot->xAxis, newPlot->yAxis);
    newPlot->graph(0)->setPen(QPen(QPen(Qt::blue)));
    newPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    newPlot->graph(0)->setData(xQData, yQData);
    newPlot->graph(0)->rescaleAxes();

    newPlot->xAxis->setLabel(xQLabel);


    if(plotType == DEC) {
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    newPlot->xAxis->setTicker(logTicker);
    newPlot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    }

    newPlot->yAxis->setLabel(yQLabel);

    newPlot->replot();
    newPlot->setMinimumSize(450, 300);

    newPlot->setAttribute(Qt::WA_DeleteOnClose);
    newPlot->show();
}


