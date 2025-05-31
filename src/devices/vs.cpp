#include "device.h"
#include "../analyser/analyser.h"
using namespace arma;

void Vs::stampDC(Analyser* analyser){
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    analyser->mna(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
    
    analyser->rhs(this->bTypeDeviceNo+analyser->nodeNum,0) += dc_value;
};

void Vs::stampAC(Analyser* analyser){
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
    analyser->mna(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
    
    analyser->rhs(this->bTypeDeviceNo+analyser->nodeNum,0) += ac_value;

};

void Vs::stampTRAN(Analyser* analyser,bool initFlag){
    if(initFlag){
        analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
        analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
        analyser->mnaTranInit(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranInit(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
        

        analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
        analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;
        analyser->mnaTranNext(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranNext(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
            }
    else{
        double stampValue = 0;
        if(sinTRAN.enabled){
            stampValue = sinTRAN.getSinValue(analyser->tranTime);
        }
        else if(pulseTRAN.enabled){
            stampValue = pulseTRAN.getPulseValue(analyser->tranTime);
        }
        else{
            stampValue = dc_value;
        }
        analyser->rhsTranNext(this->bTypeDeviceNo+analyser->nodeNum -1) = 
        analyser->rhsTranInit(this->bTypeDeviceNo+analyser->nodeNum) + stampValue; //-1 for excluding the ground node
    }
};
