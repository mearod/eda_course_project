#include "all_device.h"
#include "../analyser/analyser.h"


using namespace arma;

void Vccs::stampDC(Analyser* analyser){
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[posC].id) += g_value;
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[negC].id) -= g_value;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[posC].id) -= g_value;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[negC].id) += g_value;
};

void Vccs::stampAC(Analyser* analyser){
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[posC].id) += g_value;
    analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[negC].id) -= g_value;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[posC].id) -= g_value;
    analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[negC].id) += g_value;
};

void Vccs::stampTRAN(Analyser* analyser,bool initFlag){
    if(initFlag){
        analyser->mnaTranInit(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[posC].id) += g_value;
        analyser->mnaTranInit(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[negC].id) -= g_value;
        analyser->mnaTranInit(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[posC].id) -= g_value;
        analyser->mnaTranInit(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[negC].id) += g_value;


        analyser->mnaTranNext(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[posC].id) += g_value;
        analyser->mnaTranNext(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[negC].id) -= g_value;
        analyser->mnaTranNext(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[posC].id) -= g_value;
        analyser->mnaTranNext(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[negC].id) += g_value;
    }
    else{
        //do nothing
    }
};

double Vccs::getIDC(Analyser* analyser)
{
    return g_value*
    real(
        (analyser->circuit->nodemap[posC].isGround ? 0 : analyser->x(analyser->circuit->nodemap[posC].id)) 
        - (analyser->circuit->nodemap[negC].isGround ? 0 : analyser->x(analyser->circuit->nodemap[negC].id))
    );
};

complex<double> Vccs::getIAC(Analyser* analyser)
{
    return g_value*
    (
        (analyser->circuit->nodemap[posC].isGround ? 0 : analyser->x(analyser->circuit->nodemap[posC].id)) 
        - (analyser->circuit->nodemap[negC].isGround ? 0 : analyser->x(analyser->circuit->nodemap[negC].id))
    );
};
double Vccs::getITRAN(Analyser* analyser)
{
    return g_value*
    real(
        (analyser->circuit->nodemap[posC].isGround ? 0 : analyser->xTran(analyser->circuit->nodemap[posC].id)) 
        - (analyser->circuit->nodemap[negC].isGround ? 0 : analyser->xTran(analyser->circuit->nodemap[negC].id))
    );
};
