#include "device.h"
#include "../analyser/analyser.h"


using namespace arma;

void Inductor::stampDC(Analyser* analyser){
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    analyser->mna(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
};

void Inductor::stampAC(Analyser* analyser){
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    analyser->mna(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;

    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,this->bTypeDeviceNo+analyser->nodeNum) += -std::complex<double>((double)0, (double)2 * M_PI * analyser->freq * this->l_value);
};

void Inductor::stampTRAN(Analyser* analyser,bool initFlag){
    if(initFlag){
        currentTRAN = 0;
        analyser->mnaTranInit(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranInit(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
        analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
        analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;


        analyser->mnaTranNext(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranNext(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
        analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
        analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    }
    else{
        currentTRAN = analyser->xTran(this->bTypeDeviceNo+analyser->nodeNum-1);

        analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum -1,this->bTypeDeviceNo+analyser->nodeNum -1) = 
        analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,this->bTypeDeviceNo+analyser->nodeNum) - l_value / analyser->tranStep;

        analyser->rhsTranNext(this->bTypeDeviceNo+analyser->nodeNum -1) = 
        analyser->rhsTranInit(this->bTypeDeviceNo+analyser->nodeNum) - (currentTRAN  * l_value) / analyser->tranStep; //-1 for excluding the ground node
    }
};