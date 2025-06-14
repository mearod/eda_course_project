#include "all_device.h"
#include "../analyser/analyser.h"


using namespace arma;

bool Ccvs::findVs(Circuit* circuit){
    for (auto it = circuit->devices.begin();it!=circuit->devices.end();it++){
        if((*it)->name == this->vsName){
            this->posC = dynamic_cast<Vs*>(*it)->pos;
            this->negC = dynamic_cast<Vs*>(*it)->neg;
            this->vsBTypeDeviceNo = dynamic_cast<Vs*>(*it)->bTypeDeviceNo;
            return 1;
        }
    }
    return 0;
};

void Ccvs::stampDC(Analyser* analyser){
    analyser->mna(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;

    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;

    analyser->mna(analyser->circuit->nodemap[posC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[negC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -1;

    analyser->mna(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += 1;
    analyser->mna(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += -1;

    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,this->vsBTypeDeviceNo+analyser->nodeNum) -= ccvs_value;
};


void Ccvs::stampAC(Analyser* analyser){
    analyser->mna(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;

    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;

    analyser->mna(analyser->circuit->nodemap[posC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += 1;
    analyser->mna(analyser->circuit->nodemap[negC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -1;

    analyser->mna(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += 1;
    analyser->mna(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += -1;

    analyser->mna(this->bTypeDeviceNo+analyser->nodeNum,this->vsBTypeDeviceNo+analyser->nodeNum) -= ccvs_value;
};

void Ccvs::stampTRAN(Analyser* analyser,bool initFlag){
    if(initFlag){
        analyser->mnaTranInit(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranInit(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;

        analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
        analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;

        analyser->mnaTranInit(analyser->circuit->nodemap[posC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranInit(analyser->circuit->nodemap[negC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -1;

        analyser->mnaTranInit(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += 1;
        analyser->mnaTranInit(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += -1;

        analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,this->vsBTypeDeviceNo+analyser->nodeNum) -= ccvs_value;


        analyser->mnaTranNext(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranNext(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;

        analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) += 1;
        analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) += -1;

        analyser->mnaTranNext(analyser->circuit->nodemap[posC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranNext(analyser->circuit->nodemap[negC].id,this->vsBTypeDeviceNo+analyser->nodeNum) += -1;

        analyser->mnaTranNext(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += 1;
        analyser->mnaTranNext(this->vsBTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += -1;

        analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum,this->vsBTypeDeviceNo+analyser->nodeNum) -= ccvs_value;
    }
    else{
        //do nothing
    }
};

double Ccvs::getIDC(Analyser* analyser)
{
    return real(analyser->x(this->bTypeDeviceNo+analyser->nodeNum - 1));
};

complex<double> Ccvs::getIAC(Analyser* analyser)
{
    return analyser->x(this->bTypeDeviceNo+analyser->nodeNum - 1);
};

double Ccvs::getITRAN(Analyser* analyser)
{
    return analyser->xTran(this->bTypeDeviceNo+analyser->nodeNum - 1);
};