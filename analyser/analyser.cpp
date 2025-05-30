#include "analyser.h"
#include <assert.h>
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

void Analyser::analyseDC(string scannedDevice,double start,double end,double step){
    
    double scanValue = 0;
    BaseDevice* scanDevice = NULL;
    scanValue = start;

    for (auto it = circuit->devices.begin();it!=circuit->devices.end();it++){
        //cout<<"find:"<<(*it)->name<<std::endl;
        if((*it)->name == scannedDevice){
            scanDevice = (*it);
        }
    }//find scanned device

    assert(scanDevice);

    while(scanValue <= end){
        scanDevice->valueUpdate(scanValue);
        analyseStepDC();
        matrixNodeRecord(scanValue,resultRecorderDC);
        scanValue += step;
    }
    resultRecorderDC->debug_print();
    resultRecorderDC->debugPlotAllRecords();
}

void Analyser::analyseAC(int denseNum,double start,double end){
    double freqLevel = start;
    double levelStep = 1/(double)denseNum;
    freq = freqLevel;
    while(freqLevel < end){
        while(freq < freqLevel*10 && freq < end)
        {
            analyseStepAC();
            matrixNodeRecord(freq,resultRecorderAC);
            this->freq += levelStep*(double)9*freqLevel;
        }
        freqLevel *= 10;
        freq = freqLevel;
    }

    resultRecorderAC->debug_print();
}

void Analyser::analyseTRAN(double start,double end,double step){

}

void Analyser::matrixNodeRecord(double scanValue,ResultRecorder* resultRecorder){
    for (auto it = circuit->nodemap.begin();it!=circuit->nodemap.end();it++){
        double yRecord = circuit->nodemap[it->first].isGround? 0 : abs(x(circuit->nodemap[it->first].id));
        resultRecorder->addRecord(it->first,scanValue,yRecord);
    }
}