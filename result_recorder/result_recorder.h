#ifndef _RESULT_RECODER_H_
#define _RESULT_RECODER_H_

#include <vector>
#include <string>
#include <map>
#include "../plotter/plotter.h"
using namespace std;

class SingleRecord
{
public:
    struct Point{
        double x;
        double y;
    };
    string description;
    vector<Point> recordData;

    SingleRecord(string description):description(description) {};
    void pointRecord(double x,double y);
    void debug_print();
    void plotNewWindow(string xLabel,string yLabel,PlotType plotType=LINEAR);
};

class ResultRecorder
{
private:

public:
    int recordsNum;
    map<string,SingleRecord*> records;

    ResultRecorder();
    ~ResultRecorder();

    int addRecord(string description,double x,double y); //return single record index;
    void debug_print();

    void debugPlotAllRecords();
};

#endif