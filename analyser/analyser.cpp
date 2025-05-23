#include "analyser.h"
#include <armadillo>

Analyser::Analyser(Circuit* circuit){
    this->circuit = circuit;
    nodeNum = circuit->node_num;
    bTypeDeviceNum = 0;
    bTypeDeviceCounter = 0;
    mna.zeros();
    mna.set_size(1,1);
}

Analyser::~Analyser(){
    //do nothing
}

void Analyser::analyseDC(){
    nodeNum = circuit->node_num;
    bTypeDeviceCounter = 0;
    bTypeDeviceNum = 0;
    for (int i=0; i < circuit->devices.size(); i++){
        if(circuit->devices[i]->deviceType == B_TYPE){
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

void Analyser::analyseAC(){
    freq = 10;
    nodeNum = circuit->node_num;
    bTypeDeviceCounter = 0;
    bTypeDeviceNum = 0;
    for (int i=0; i < circuit->devices.size(); i++){
        if(circuit->devices[i]->deviceType == B_TYPE){
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
    mat mna_real = real(mna);
    vec rhs_real = real(rhs);
    mna_real.print("nmaDC:");
    rhs_real.print("rhsDC:");
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
    mna.print("nmaAC:");
    rhs.print("rhsAC:");
}

void Analyser::solveDC(){
    mna.shed_col(nodeNum-1);
    mna.shed_row(nodeNum-1);
    rhs.shed_row(nodeNum-1);//delete ground node
    cx_vec x;
    bool status = solve(x, mna, rhs, arma::solve_opts::allow_ugly);
    x.print("x:");
}

void Analyser::solveAC(){
    mna.shed_col(nodeNum-1);
    mna.shed_row(nodeNum-1);
    rhs.shed_row(nodeNum-1);//delete ground node
    cx_vec x;
    bool status = solve(x, mna, rhs, arma::solve_opts::allow_ugly);
    x.print("x:");
}

