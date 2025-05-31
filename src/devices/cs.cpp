#include "device.h"
#include "../analyser/analyser.h"


using namespace arma;

void Cs::stampDC(Analyser* analyser){
    analyser->rhs(analyser->circuit->nodemap[pos].id,0) -= dc_value;
    analyser->rhs(analyser->circuit->nodemap[neg].id,0) += dc_value;
};

void Cs::stampAC(Analyser* analyser){
    analyser->rhs(analyser->circuit->nodemap[pos].id,0) -= ac_value;
    analyser->rhs(analyser->circuit->nodemap[neg].id,0) += ac_value;
};

void Cs::stampTRAN(Analyser* analyser,bool initFlag){
    if(initFlag){
        analyser->rhsTranInit(analyser->circuit->nodemap[pos].id,0) -= dc_value;
        analyser->rhsTranInit(analyser->circuit->nodemap[neg].id,0) += dc_value;
    }
    else{
        double stampValue = 0;
        if(sinTRAN.enabled){
            stampValue = sinTRAN.getSinValue(analyser->tranTime);
        }
        else if(pulseTRAN.enabled){
            stampValue = pulseTRAN.getPulseValue(analyser->tranTime);
        }
        else{
            stampValue = dc_value;
        }

        if(!analyser->circuit->nodemap[pos].isGround)
        {
            analyser->rhsTranNext(analyser->circuit->nodemap[pos].id,0) 
            = analyser->rhsTranInit(analyser->circuit->nodemap[pos].id,0) - stampValue ;
        }
        if(!analyser->circuit->nodemap[neg].isGround)
        {
            analyser->rhsTranNext(analyser->circuit->nodemap[neg].id,0) 
            = analyser->rhsTranInit(analyser->circuit->nodemap[neg].id,0) + stampValue ;
        }
    }
};