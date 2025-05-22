#include "device.h"
#include "../analyser/analyser.h"


using namespace arma;

void Vcvs::stampDC(Analyser* analyser){
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += -vcvs_value;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += vcvs_value;

    analyser->mna(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
    
};

void Vcvs::stampAC(Analyser* analyser){
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += -vcvs_value;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += vcvs_value;

    analyser->mna(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
    
};