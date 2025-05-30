#include <vector>
#include <string>
#include <iostream>
#include "result_recorder.h"

using namespace std;

void SingleRecord::pointRecord(double x,double y){
    Point point;
    point.x = x;
    point.y = y;
    recordData.push_back(point);
}

ResultRecorder::ResultRecorder(){
    recordsNum = 0;
}

ResultRecorder::~ResultRecorder(){
    for (auto it = records.begin(); it != records.end(); ++it) {
        delete it->second;
    }
}

int ResultRecorder::addRecord(string description,string xLabel,string yLabel,double x,double y){
    if (records.find(description) != records.end()) {
        records[description]->pointRecord(x,y);
        records[description]->xLabel = xLabel;
        records[description]->yLabel = yLabel;
        return recordsNum;
    }
    recordsNum ++;
    SingleRecord* newRecord = new SingleRecord(description);
    newRecord->pointRecord(x,y);
    newRecord->xLabel = xLabel;
    newRecord->yLabel = yLabel;
    records[description]=newRecord;
    return recordsNum;
}

void ResultRecorder::debug_print(){
    for (auto it = records.begin(); it != records.end(); ++it) {
        cout<<"record:"<<it->first<<endl;
        it->second->debug_print();
    }
};

void SingleRecord::debug_print(){
    for (auto it = recordData.begin(); it != recordData.end(); ++it) {
        cout<<"x:"<<it->x<<" y:"<<it->y<<endl;
    }
};

void SingleRecord::plotNewWindow(PlotType plotType){
    vector<double> xData,yData;
    for (auto it = recordData.begin(); it != recordData.end(); ++it) {
        xData.push_back(it->x);
        yData.push_back(it->y);
    }
    newPlotWindow(xData,yData,xLabel,yLabel,description,plotType);
}

void ResultRecorder::debugPlotAllRecords(PlotType plotType){
    for (auto it = records.begin(); it != records.end(); ++it) {
        it->second->plotNewWindow(plotType);
    }
}