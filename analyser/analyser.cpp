#include "analyser.h"
#include <assert.h>
#include <cmath>
#include <armadillo>

Analyser::Analyser(Circuit* circuit){
    this->resultRecorderDC = new ResultRecorder;
    this->resultRecorderAC = new ResultRecorder;
    this->resultRecorderTRAN = new ResultRecorder;

    this->circuit = circuit;
    nodeNum = circuit->node_num;
    bTypeDeviceNum = 0;
    bTypeDeviceCounter = 0;
    mna.zeros();
    mna.set_size(1,1);
}

Analyser::~Analyser(){
    delete resultRecorderDC;
    delete resultRecorderAC;
    delete resultRecorderTRAN;
}

void Analyser::analyseStepDC(){
    nodeNum = circuit->node_num;
    bTypeDeviceCounter = 0;
    bTypeDeviceNum = 0;
    for (int i=0; i < circuit->devices.size(); i++){
        if(circuit->devices[i]->stampType == B_TYPE){
            dynamic_cast<BTypeDevice*>(circuit->devices[i])->bTypeDeviceNo = bTypeDeviceNum;
            bTypeDeviceNum ++; //统计会增加矩阵branch类型的器件数量
        }
    }

    mna.set_size(nodeNum+bTypeDeviceNum,nodeNum+bTypeDeviceNum);
    mna.zeros();

    rhs.set_size(nodeNum+bTypeDeviceNum);
    rhs.zeros();

    this->devicesStampDC();

    this->solveDC();
}

void Analyser::analyseStepAC(){
    nodeNum = circuit->node_num;
    bTypeDeviceCounter = 0;
    bTypeDeviceNum = 0;
    for (int i=0; i < circuit->devices.size(); i++){
        if(circuit->devices[i]->stampType == B_TYPE){
            dynamic_cast<BTypeDevice*>(circuit->devices[i])->bTypeDeviceNo = bTypeDeviceNum;
            bTypeDeviceNum ++;
        }
    }

    mna.set_size(nodeNum+bTypeDeviceNum,nodeNum+bTypeDeviceNum);
    mna.zeros();

    rhs.set_size(nodeNum+bTypeDeviceNum);
    rhs.zeros();

    this->devicesStampAC();

    this->solveAC();
}

void Analyser::devicesStampDC(){

    for (auto it = circuit->nodemap.begin();it!=circuit->nodemap.end();it++){
        if(it->second.isGround){
            it->second.id = nodeNum - 1;//ground node id re-set
            break;
        }
    }
    for (int i=0; i < circuit->devices.size(); i++){
        circuit->devices[i]->stampDC(this);
    }
    mat mna_display = real(mna);
    vec rhs_display = real(rhs);
    mna_display.print("nmaDC(including ground):");
    rhs_display.print("rhsDC(including ground):");
    printf("\n");

    mna_display.shed_col(nodeNum-1);
    mna_display.shed_row(nodeNum-1);
    rhs_display.shed_row(nodeNum-1);//delete ground node

    mna_display.print("nmaDC(excluding ground):");
    rhs_display.print("rhsDC(excluding ground):");
    printf("\n");
}

void Analyser::devicesStampAC(){
    int i = 0; //re rank
    for (auto it = circuit->nodemap.begin();it!=circuit->nodemap.end();it++){
        if(it->second.isGround){
            it->second.id = nodeNum - 1;//ground node id re-set
            break;
        }
    }
    
    for (int i=0; i < circuit->devices.size(); i++){
        circuit->devices[i]->stampAC(this);
    }

    cx_mat mna_display = mna;
    cx_vec rhs_display = rhs;
    mna_display.print("nmaAC(including ground):");
    rhs_display.print("rhsAC(including ground):");
    printf("\n");

    mna_display.shed_col(nodeNum-1);
    mna_display.shed_row(nodeNum-1);
    rhs_display.shed_row(nodeNum-1);//delete ground node

    mna_display.print("nmaAC(excluding ground):");
    rhs_display.print("rhsAC(excluding ground):");
    printf("\n");
}

void Analyser::solveDC(){
    mna.shed_col(nodeNum-1);
    mna.shed_row(nodeNum-1);
    rhs.shed_row(nodeNum-1);//delete ground node
    bool status = solve(x, mna, rhs, arma::solve_opts::allow_ugly);
    real(x).print("dc solve result:");
    printf("\n");
}

void Analyser::solveAC(){
    mna.shed_col(nodeNum-1);
    mna.shed_row(nodeNum-1);
    rhs.shed_row(nodeNum-1);//delete ground node
    bool status = solve(x, mna, rhs, arma::solve_opts::allow_ugly);
    x.print("ac solve result:");
    printf("\n");
}

void Analyser::createSingleRecord(){

}

void Analyser::analyseDC(){
    if(checkPlotNodeExists() == false){
        return;
    }
    string sourceName = circuit->commandDC.sourceName;
    double start = circuit->commandDC.startValue;
    double end = circuit->commandDC.endValue;
    double step = circuit->commandDC.stepValue;

    double scanValue = 0;
    BaseDevice* sourceDevice = NULL;
    scanValue = start;

    for (auto it = circuit->devices.begin();it!=circuit->devices.end();it++){
        //cout<<"find:"<<(*it)->name<<std::endl;
        if((*it)->name == sourceName){
            sourceDevice = (*it);
        }
    }//find scanned device

    if(sourceDevice == NULL)
    {
        cout<<"DC analyse error: source device not found,please ensure the source device exists in the circuit."<<std::endl;
        return;
    }

    while(scanValue <= end){
        sourceDevice->valueUpdate(scanValue);
        analyseStepDC();
        matrixNodeRecordDC(scanValue,resultRecorderDC);
        scanValue += step;
    }
    resultRecorderDC->debug_print();
    resultRecorderDC->debugPlotAllRecords();
}

void Analyser::analyseAC(){
    if(checkPlotNodeExists() == false){
        return;
    }
    int denseNum = circuit->commandAC.numPerDec;
    double start = circuit->commandAC.startFreq;
    double end = circuit->commandAC.endFreq;

    double freqLevel = start;
    double levelStep = 1/(double)denseNum;
    freq = freqLevel;
    while(freqLevel < end){
        while(freq < freqLevel*10 && freq < end)
        {
            analyseStepAC();
            matrixNodeRecordAC(freq,resultRecorderAC);
            this->freq += levelStep*(double)9*freqLevel;
        }
        freqLevel *= 10;
        freq = freqLevel;
    }

    resultRecorderAC->debug_print();
    resultRecorderAC->debugPlotAllRecords(DEC);
}

void Analyser::analyseTRAN(){
    if(checkPlotNodeExists() == false){
        return;
    }
}

void Analyser::matrixNodeRecordDC(double scanValue,ResultRecorder* resultRecorder){
    for (auto it = circuit->commandPlot.nodePlotQueue.begin();it!=circuit->commandPlot.nodePlotQueue.end();it++){
        double yRecord = circuit->nodemap[it->nodeName].isGround? 0 : abs(x(circuit->nodemap[it->nodeName].id));
        string description = it->prefix+it->nodeName;
        string xLabel = circuit->commandDC.sourceName;
        string yLabel = it->prefix;
        resultRecorder->addRecord(description,xLabel,yLabel,scanValue,yRecord);
    }
}

void Analyser::matrixNodeRecordAC(double scanValue,ResultRecorder* resultRecorder){
    for (auto it = circuit->commandPlot.nodePlotQueue.begin();it!=circuit->commandPlot.nodePlotQueue.end();it++){
        double yRecord = circuit->nodemap[it->nodeName].isGround? 0 : abs(x(circuit->nodemap[it->nodeName].id));
        string description = it->prefix+it->nodeName;
        resultRecorder->addRecord(description,"Frequency(Hz)","dB",scanValue,20*log10(yRecord));
    }
}

bool Analyser::checkPlotNodeExists(){
    for (auto it = circuit->commandPlot.nodePlotQueue.begin();it!=circuit->commandPlot.nodePlotQueue.end();it++){
         if(circuit->nodemap.find(it->nodeName) == circuit->nodemap.end()){
            cout<<"Plot command error: node "<<it->nodeName<<" does not exists in the circuit."<<std::endl;
            return false;
         }
    }
    return true;
}