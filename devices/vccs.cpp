#include "device.h"
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