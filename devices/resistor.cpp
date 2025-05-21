#include "device.h"
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