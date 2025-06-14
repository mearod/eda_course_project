#include "all_device.h"
#include "../analyser/analyser.h"
#include <assert.h>

using namespace arma;

bool Cccs::findVs(Circuit* circuit){

    for (auto it = circuit->devices.begin();it!=circuit->devices.end();it++){
        //cout<<"find:"<<(*it)->name<<std::endl;
        if((*it)->name == this->vsName){
            this->posC = dynamic_cast<Vs*>(*it)->pos;
            this->negC = dynamic_cast<Vs*>(*it)->neg;
            this->vsBTypeDeviceNo = dynamic_cast<Vs*>(*it)->bTypeDeviceNo;
            return 1;
        }
    }
    return 0;
};

void Cccs::stampDC(Analyser* analyser){

    assert(findVs(analyser->circuit));

    analyser->mna(analyser->circuit->nodemap[posC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[negC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -1;

    analyser->mna(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += 1;
    analyser->mna(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += -1;

    analyser->mna(analyser->circuit->nodemap[pos].id,this->vsBTypeDeviceNo+analyser->nodeNum) += cccs_value;
    analyser->mna(analyser->circuit->nodemap[neg].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -cccs_value;

};


void Cccs::stampAC(Analyser* analyser){

    assert(findVs(analyser->circuit));

    analyser->mna(analyser->circuit->nodemap[posC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[negC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -1;

    analyser->mna(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += 1;
    analyser->mna(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += -1;

    analyser->mna(analyser->circuit->nodemap[pos].id,this->vsBTypeDeviceNo+analyser->nodeNum) += cccs_value;
    analyser->mna(analyser->circuit->nodemap[neg].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -cccs_value;

};

void Cccs::stampTRAN(Analyser* analyser,bool initFlag){
    if(initFlag){

        assert(findVs(analyser->circuit));

        analyser->mnaTranInit(analyser->circuit->nodemap[posC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranInit(analyser->circuit->nodemap[negC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -1;

        analyser->mnaTranInit(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += 1;
        analyser->mnaTranInit(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += -1;

        analyser->mnaTranInit(analyser->circuit->nodemap[pos].id,this->vsBTypeDeviceNo+analyser->nodeNum) += cccs_value;
        analyser->mnaTranInit(analyser->circuit->nodemap[neg].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -cccs_value;


        analyser->mnaTranNext(analyser->circuit->nodemap[posC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranNext(analyser->circuit->nodemap[negC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -1;

        analyser->mnaTranNext(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += 1;
        analyser->mnaTranNext(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += -1;

        analyser->mnaTranNext(analyser->circuit->nodemap[pos].id,this->vsBTypeDeviceNo+analyser->nodeNum) += cccs_value;
        analyser->mnaTranNext(analyser->circuit->nodemap[neg].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -cccs_value;
    }
    else{
        //do nothing
    }
};

double Cccs::getIDC(Analyser* analyser)
{
    return real(analyser->x(this->bTypeDeviceNo+analyser->nodeNum - 1));
};

complex<double> Cccs::getIAC(Analyser* analyser)
{
    return analyser->x(this->bTypeDeviceNo+analyser->nodeNum - 1);
};

double Cccs::getITRAN(Analyser* analyser)
{
    return analyser->xTran(this->bTypeDeviceNo+analyser->nodeNum - 1);
};