#include "analyser.h"
#include <assert.h>
#include <cmath>
#include <armadillo>

Analyser::Analyser(Circuit* circuit){
    this->resultRecorderDC = new ResultRecorder;
    this->resultRecorderAC = new ResultRecorder;
    this->resultRecorderTRAN = new ResultRecorder;

    this->circuit = circuit;
    nodeNum = circuit->node_num;
    bTypeDeviceNum = 0;
    bTypeDeviceCounter = 0;
    mna.zeros();
    mna.set_size(1,1);
}

Analyser::~Analyser(){
    delete resultRecorderDC;
    delete resultRecorderAC;
    delete resultRecorderTRAN;
}

void Analyser::createSingleRecord(){

}

bool Analyser::checkPlotNodeExists(){
    for (auto it = circuit->commandPlot.nodePlotQueue.begin();it!=circuit->commandPlot.nodePlotQueue.end();it++){
        if(it->prefix=="V")
        {
            if(circuit->nodemap.find(it->nodeName) == circuit->nodemap.end()){
                cout<<"Plot command error: node "<<it->nodeName<<" does not exists in the circuit."<<std::endl;
                return false;
             }
        }
        else if(it->prefix=="I")
        {
            if(circuit->namemap.find(it->nodeName) == circuit->namemap.end()){
                cout<<"Plot command error: device "<<it->nodeName<<" does not exists in the circuit."<<std::endl;
                return false;
            }
        }
        else{assert(0);}
    }
    return true;
}


void Analyser::opResultPrint(){
    string resultInfo = "OP RESULT:\n";
    for (auto it = circuit->commandPlot.nodePlotQueue.begin();it!=circuit->commandPlot.nodePlotQueue.end();it++){
        double nodeResult = circuit->nodemap[it->nodeName].isGround? 0 : real(x(circuit->nodemap[it->nodeName].id));
        resultInfo += it->prefix+it->nodeName+": "+to_string(nodeResult)+"\n";
    }
    logOutput(resultInfo,false);
}

void Analyser::solveIte(){
    mnaIte.shed_col(nodeNum-1);
    mnaIte.shed_row(nodeNum-1);
    rhsIte.shed_row(nodeNum-1);//delete ground node
    bool status = solve(xIte, mnaIte, rhsIte, arma::solve_opts::allow_ugly);
    real(xIte).print("iteration solve result:");
    printf("\n");
}

