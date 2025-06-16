#include "analyser.h"
#include <assert.h>
#include <cmath>
#include <armadillo>

void Analyser::analyseStepDC(){
    nodeNum = circuit->node_num;
    bTypeDeviceCounter = 0;
    bTypeDeviceNum = 0;
    for (int i=0; i < circuit->devices.size(); i++){
        if(circuit->devices[i]->stampType == B_TYPE && circuit->devices[i]->type != C){ //capacitor doesn't need to be bType device in AC analysis
            circuit->devices[i]->bTypeDeviceNo = bTypeDeviceNum;
            bTypeDeviceNum ++; //统计会增加矩阵branch类型的器件数量
        }
    }

    mna.set_size(nodeNum+bTypeDeviceNum,nodeNum+bTypeDeviceNum);
    mna.zeros();

    rhs.set_size(nodeNum+bTypeDeviceNum);
    rhs.zeros();

    this->devicesStampDC();

    mna.shed_col(nodeNum-1);
    mna.shed_row(nodeNum-1);
    rhs.shed_row(nodeNum-1);//delete ground node

    //non-linear part iteration
    mnaIte = mna;
    rhsIte = rhs;




    if(!IterationSolve(10))
    {
        logOutput("DC iteration failed after 10 times iteration.",true);
    }


    mna = mnaIte;
    rhs = rhsIte;


    this->solveDC();
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

void Analyser::solveDC(){
    bool status = solve(x, mna, rhs, arma::solve_opts::allow_ugly);
    real(x).print("dc solve result:");
    printf("\n");
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
        logOutput("DC analyse error: source device not found,please ensure the source device exists in the circuit.",true);
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

void Analyser::matrixNodeRecordDC(double scanValue,ResultRecorder* resultRecorder){
    for (auto it = circuit->commandPlot.nodePlotQueue.begin();it!=circuit->commandPlot.nodePlotQueue.end();it++){
        string description = it->prefix+it->nodeName;
        string xLabel = circuit->commandDC.sourceName;
        string yLabel = it->prefix;
        if(it->prefix == "V")
        {
            double yRecord = circuit->nodemap[it->nodeName].isGround? 0 : real(x(circuit->nodemap[it->nodeName].id));
            resultRecorder->addRecord(description,xLabel,yLabel,scanValue,yRecord);
        }
        else if(it->prefix == "I")
        {   
            double yRecord = circuit->devices[circuit->namemap[it->nodeName]]->getIDC(this);
            resultRecorder->addRecord(description,xLabel,yLabel,scanValue,yRecord);
        }
        else{assert(0);}
    }
}