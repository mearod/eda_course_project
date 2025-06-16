#include <math.h>
#include <string>
#include "all_device.h"
#include "../analyser/analyser.h"
using namespace std;

#define ABOSOLUTE_ERROR 1e-6
#define RELATIVE_ERROR 1e-3

Diode::Diode(std::string name,string model,string pos, string neg, double Vd,double Is, double Vt):
BaseDevice(name,G_TYPE,D,true), NonlinearDevice(),model(model),pos(pos),neg(neg)
{
    this->Is = 2e-14;
    this->Vt = 0.026;
    this->Vd = 0.7;
    this->Id = Is * (exp(this->Vd/Vt) - 1);
    this->lastVd = 0;
    this->lastId = 0;
    this->isNonLinearDevice = true;
}

void Diode::stampDC(Analyser* analyser){
    //do nothing
};

void Diode::stampAC(Analyser* analyser){
    //do nothing
};

void Diode::stampTRAN(Analyser* analyser,bool initFlag){
    //do nothing
};

void Diode::stampIteration(Analyser* analyser,bool isFirstStamp){

    double g = Is/Vt*exp(Vd/Vt);
    double j = Id-g*Vd;

    double lastg = isFirstStamp ? 0 : Is/Vt*exp(lastVd/Vt);
    double lastj = isFirstStamp ? 0 : lastId - lastg*lastVd ;


    if(!analyser->circuit->nodemap[pos].isGround)
    {
        analyser->mnaIte(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[pos].id) += g - lastg;
        analyser->rhsIte(analyser->circuit->nodemap[pos].id,0) -= j - lastj;

        if(!analyser->circuit->nodemap[neg].isGround)
        {
            analyser->mnaIte(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[pos].id) -= g - lastg;
            analyser->mnaIte(analyser->circuit->nodemap[pos].id,analyser->circuit->nodemap[neg].id) -= g - lastg;
            analyser->mnaIte(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[neg].id) += g - lastg;
            analyser->rhsIte(analyser->circuit->nodemap[neg].id,0) += j - lastj;
        }
    }
    else if(!analyser->circuit->nodemap[neg].isGround)
    {
        analyser->mnaIte(analyser->circuit->nodemap[neg].id,analyser->circuit->nodemap[neg].id) += g - lastg;
        analyser->rhsIte(analyser->circuit->nodemap[neg].id,0) += j - lastj;
    }
    

};

void Diode::NonlinearValueIteration(Analyser* analyser){
    lastVd = Vd;
    lastId = Id;
    Vd = 
    real(
    (analyser->circuit->nodemap[pos].isGround ? 0 : analyser->xIte(analyser->circuit->nodemap[pos].id)) 
    - (analyser->circuit->nodemap[neg].isGround ? 0 : analyser->xIte(analyser->circuit->nodemap[neg].id))
    );
    Id = Is * (exp(Vd/Vt) - 1);

}

bool Diode::checkConvergence(){
    if(abs(Vd-lastVd)<ABOSOLUTE_ERROR && abs(Vd-lastVd)<RELATIVE_ERROR*abs(lastVd))
        return true;
    else
        return false;
};

double Diode::getIDC(Analyser* analyser)
{
    return Id;
};

complex<double> Diode::getIAC(Analyser* analyser)
{
    return Id;
};

double Diode::getITRAN(Analyser* analyser)
{
    return Id;
};