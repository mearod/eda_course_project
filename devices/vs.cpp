#include "device.h"
#include "../analyser/analyser.h"
using namespace arma;

void Vs::stampDC(Analyser* analyser){
    analyser->mna(analyser->bTypeDeviceCounter+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(analyser->bTypeDeviceCounter+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += -1;
    
    analyser->rhs(analyser->bTypeDeviceCounter+analyser->nodeNum,0) += vs_value;
    
    bTypeDeviceNo = analyser->bTypeDeviceCounter;
    analyser->bTypeDeviceCounter ++;
};

void Vs::stampAC(Analyser* analyser){
    analyser->mna(analyser->bTypeDeviceCounter+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(analyser->bTypeDeviceCounter+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += -1;
    
    analyser->rhs(analyser->bTypeDeviceCounter+analyser->nodeNum,0) += vs_value;
    
    bTypeDeviceNo = analyser->bTypeDeviceCounter;
    analyser->bTypeDeviceCounter ++;
};
