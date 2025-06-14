#include "analyser.h"
#include <assert.h>
#include <cmath>
#include <armadillo>

void Analyser::analyseStepAC(){
    nodeNum = circuit->node_num;
    bTypeDeviceCounter = 0;
    bTypeDeviceNum = 0;
    for (int i=0; i < circuit->devices.size(); i++){
        if(circuit->devices[i]->stampType == B_TYPE && circuit->devices[i]->type != C){ //capacitor doesn't need to be bType device in AC analysis
            circuit->devices[i]->bTypeDeviceNo = bTypeDeviceNum;
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

void Analyser::solveAC(){
    mna.shed_col(nodeNum-1);
    mna.shed_row(nodeNum-1);
    rhs.shed_row(nodeNum-1);//delete ground node
    bool status = solve(x, mna, rhs, arma::solve_opts::allow_ugly);
    x.print("ac solve result:");
    printf("\n");
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

void Analyser::matrixNodeRecordAC(double scanValue,ResultRecorder* resultRecorder){
    for (auto it = circuit->commandPlot.nodePlotQueue.begin();it!=circuit->commandPlot.nodePlotQueue.end();it++){
        double ampRecord = circuit->nodemap[it->nodeName].isGround? 0 : abs(x(circuit->nodemap[it->nodeName].id));
        double phaseRecord = circuit->nodemap[it->nodeName].isGround? 0 : arg(x(circuit->nodemap[it->nodeName].id));
        string description = it->prefix+it->nodeName;
        resultRecorder->addRecord(description+"_amplitude","Frequency(Hz)","dB",scanValue,20*log10(ampRecord));
        resultRecorder->addRecord(description+"_phase","Frequency(Hz)","Phase(rad)",scanValue,phaseRecord);
    }
}
