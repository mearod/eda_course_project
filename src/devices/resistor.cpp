#include "all_device.h"
#include "../analyser/analyser.h"


using namespace arma;

void Resistor::stampDC(Analyser* analyser){
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[pos].id) += 1/r_value;
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[neg].id) -= 1/r_value;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[pos].id) -= 1/r_value;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[neg].id) += 1/r_value;
};

void Resistor::stampAC(Analyser* analyser){
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[pos].id) += 1/r_value;
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[neg].id) -= 1/r_value;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[pos].id) -= 1/r_value;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[neg].id) += 1/r_value;
};

void Resistor::stampTRAN(Analyser* analyser,bool initFlag){
    if(initFlag){
        analyser->mnaTranInit(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[pos].id) += 1/r_value;
        analyser->mnaTranInit(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[neg].id) -= 1/r_value;
        analyser->mnaTranInit(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[pos].id) -= 1/r_value;
        analyser->mnaTranInit(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[neg].id) += 1/r_value;


        analyser->mnaTranNext(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[pos].id) += 1/r_value;
        analyser->mnaTranNext(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[neg].id) -= 1/r_value;
        analyser->mnaTranNext(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[pos].id) -= 1/r_value;
        analyser->mnaTranNext(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[neg].id) += 1/r_value;
    }
    else{
        //do nothing
    }
};

double Resistor::getIDC(Analyser* analyser)
{
    return 1/r_value*
    real(
        (analyser->circuit->nodemap[pos].isGround ? 0 : analyser->x(analyser->circuit->nodemap[pos].id)) 
        - (analyser->circuit->nodemap[neg].isGround ? 0 : analyser->x(analyser->circuit->nodemap[neg].id))
    );
};

complex<double> Resistor::getIAC(Analyser* analyser)
{
    return 1/r_value*
    (
        (analyser->circuit->nodemap[pos].isGround ? 0 : analyser->x(analyser->circuit->nodemap[pos].id)) 
        - (analyser->circuit->nodemap[neg].isGround ? 0 : analyser->x(analyser->circuit->nodemap[neg].id))
    );
};
double Resistor::getITRAN(Analyser* analyser)
{
    return 1/r_value*
    real(
        (analyser->circuit->nodemap[pos].isGround ? 0 : analyser->xTran(analyser->circuit->nodemap[pos].id)) 
        - (analyser->circuit->nodemap[neg].isGround ? 0 : analyser->xTran(analyser->circuit->nodemap[neg].id))
    );
};