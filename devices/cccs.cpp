#include "device.h"
#include "../analyser/analyser.h"


using namespace arma;

void Cccs::stampDC(Analyser* analyser){
    // circuit->namemap.find(device_name) != circuit->namemap.end()
    // std::string posC = analyser->circuit->devices.find();
    // std::string negC;

    // analyser->mna(analyser->circuit->nodemap[posC].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += 1;
    // analyser->mna(analyser->circuit->nodemap[negC].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += -1;

    // analyser->mna(analyser->bTypeDeviceCounter+analyser->nodeNum,analyser->circuit->nodemap[posC].id) += 1;
    // analyser->mna(analyser->bTypeDeviceCounter+analyser->nodeNum,analyser->circuit->nodemap[negC].id) += -1;

    // analyser->mna(analyser->circuit->nodemap[pos].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += cccs_value;
    // analyser->mna(analyser->circuit->nodemap[neg].id,analyser->bTypeDeviceCounter+analyser->nodeNum) += -cccs_value;

    // analyser->rhs(analyser->bTypeDeviceCounter+analyser->nodeNum,0) += vs_value;
};


void Cccs::stampAC(Analyser* analyser){
    // analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[posC].id) += 1/g_value;
    // analyser->mna(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[negC].id) -= 1/g_value;
    // analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[posC].id) -= 1/g_value;
    // analyser->mna(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[negC].id) += 1/g_value;
};