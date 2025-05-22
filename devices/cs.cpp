#include "device.h"
#include "../analyser/analyser.h"


using namespace arma;

void Cs::stampDC(Analyser* analyser){
    analyser->rhs(analyser->circuit->nodemap[pos].id,0) -= cs_value;
    analyser->rhs(analyser->circuit->nodemap[neg].id,0) += cs_value;
};

void Cs::stampAC(Analyser* analyser){
    analyser->rhs(analyser->circuit->nodemap[pos].id,0) -= cs_value;
    analyser->rhs(analyser->circuit->nodemap[neg].id,0) += cs_value;
};