#include "device.h"
#include "../analyser/analyser.h"


using namespace arma;

void Inductor::stampDC(Analyser* analyser){
    analyser->mna(analyser->bTypeDeviceCounter+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(analyser->bTypeDeviceCounter+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += -1;
    
    analyser->rhs(analyser->bTypeDeviceCounter+analyser->nodeNum,0) += 0;
};

void Inductor::stampAC(Analyser* analyser){
    analyser->mna(analyser->bTypeDeviceCounter+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(analyser->bTypeDeviceCounter+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += -1;
    
    analyser->rhs(analyser->bTypeDeviceCounter+analyser->nodeNum,0) += std::complex<double>((double)0, (double)2 * M_PI * analyser->freq * this->l_value);
};