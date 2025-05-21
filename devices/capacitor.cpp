#include "device.h"
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