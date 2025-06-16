#include "all_device.h"
#include <complex>
#include "../analyser/analyser.h"


using namespace arma;

void Capacitor::stampDC(Analyser* analyser){
    //do nothing
};

void Capacitor::stampAC(Analyser* analyser){
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[pos].id) += std::complex<double>((double)0, (double)2 * M_PI * analyser->freq * this->c_value);
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[neg].id) -= std::complex<double>((double)0, (double)2 * M_PI * analyser->freq * this->c_value);
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[pos].id) -= std::complex<double>((double)0, (double)2 * M_PI * analyser->freq * this->c_value);
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[neg].id) += std::complex<double>((double)0, (double)2 * M_PI * analyser->freq * this->c_value);
};

void Capacitor::stampTRAN(Analyser* analyser,bool initFlag){
    if(initFlag){
        voltageTRAN = 0;
        analyser->mnaTranInit(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranInit(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
        analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,this->bTypeDeviceNo+analyser->nodeNum) += -1;


        analyser->mnaTranNext(analyser->circuit->nodemap[pos].id,this->bTypeDeviceNo+analyser->nodeNum) += 1;
        analyser->mnaTranNext(analyser->circuit->nodemap[neg].id,this->bTypeDeviceNo+analyser->nodeNum) += -1;
        analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum,this->bTypeDeviceNo+analyser->nodeNum) += -1;
    }
    else{
        voltageTRAN = (analyser->circuit->nodemap[pos].isGround ? 0 : analyser->xTran(analyser->circuit->nodemap[pos].id)) 
                    - (analyser->circuit->nodemap[neg].isGround ? 0 : analyser->xTran(analyser->circuit->nodemap[neg].id));
        if(!analyser->circuit->nodemap[pos].isGround)
        {
            analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum -1,analyser->circuit->nodemap[pos].id) = 
            analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[pos].id) + c_value / analyser->tranStep;
        }
        if(!analyser->circuit->nodemap[neg].isGround)
        {
            analyser->mnaTranNext(this->bTypeDeviceNo+analyser->nodeNum -1,analyser->circuit->nodemap[neg].id) = 
            analyser->mnaTranInit(this->bTypeDeviceNo+analyser->nodeNum,analyser->circuit->nodemap[neg].id) - c_value / analyser->tranStep;
        }

        analyser->rhsTranNext(this->bTypeDeviceNo+analyser->nodeNum -1) = 
        analyser->rhsTranInit(this->bTypeDeviceNo+analyser->nodeNum) + (voltageTRAN * c_value) / analyser->tranStep; //-1 for excluding the ground node
    }
};

double Capacitor::getIDC(Analyser* analyser)
{
    return 0;
};

complex<double> Capacitor::getIAC(Analyser* analyser)
{
    return analyser->x(this->bTypeDeviceNo+analyser->nodeNum - 1);
};

double Capacitor::getITRAN(Analyser* analyser)
{
    return analyser->xTran(this->bTypeDeviceNo+analyser->nodeNum - 1);
};

double Capacitor::filterLTE(Analyser* analyser, double step) {
    double currentI = getITRAN(analyser);
    double tmp = 2*this->c_value/(std::abs(currentI-ILastTranStep))*1e-3;
    ILastTranStep = currentI;

    if (step > tmp)
        return step / 2;
    else if (step * 2 < tmp)
        return step * 2;
    else
        return step;
} 
