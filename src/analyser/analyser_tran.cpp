#include "analyser.h"
#include <assert.h>
#include <cmath>
#include <armadillo>

void Analyser::analyseStepTRAN(){
    devicesStampTRAN(false);


    //non-linear part iteration
    mnaIte = arma::cx_mat(mnaTranNext, arma::zeros<arma::mat>(size(mnaTranNext)));
    rhsIte = arma::cx_mat(rhsTranNext, arma::zeros<arma::mat>(size(rhsTranNext)));


    for(int k=0;k<20;k++)
    {
    for (int i=0; i < circuit->devices.size(); i++){
        bool firstStampFlag = (k==0);
        if(circuit->devices[i]->isNonLinearDevice == true){
            dynamic_cast<NonlinearDevice*>(circuit->devices[i])->stampIteration(this,firstStampFlag);
        }
    }

    solve(xIte, mnaIte, rhsIte, arma::solve_opts::allow_ugly);
    for (int i=0; i < circuit->devices.size(); i++){
        if(circuit->devices[i]->isNonLinearDevice == true){
            dynamic_cast<NonlinearDevice*>(circuit->devices[i])->NonlinearValueIteration(this);
        }
    }
    }
    
    solveTRAN();
}

void Analyser::devicesStampTRAN(bool initFlag){
    int i = 0; //re rank
    for (auto it = circuit->nodemap.begin();it!=circuit->nodemap.end();it++){
        if(it->second.isGround){
            it->second.id = nodeNum - 1;//ground node id re-set
            break;
        }
    }
    
    for (int i=0; i < circuit->devices.size(); i++){
        circuit->devices[i]->stampTRAN(this,initFlag);
    }
}

void Analyser::solveTRAN(){
    bool status = solve(xTran, real(mnaIte), real(rhsIte), arma::solve_opts::allow_ugly);
    xTran.print("tran solve result:");
    printf("\n");
}

void Analyser::analyseTRAN(){
    analyseInitTRAN();
    if(tranStep<0){
        cout<<"TRAN analyse error: step time cannot be negative."<<std::endl;
        return;
    }
    while(tranTime < tranStopTime){
        analyseStepTRAN();
        matrixNodeRecordTRAN(resultRecorderTRAN);
        tranTime += tranStep;
    }
    resultRecorderTRAN->debug_print();
    resultRecorderTRAN->debugPlotAllRecords();
}

void Analyser::analyseInitTRAN(){
    if(checkPlotNodeExists() == false){
        return;
    }
    tranTime = circuit->commandTRAN.startTime;
    tranStopTime = circuit->commandTRAN.stopTime;
    tranStep = (circuit->commandTRAN.stepTime < 0) ? tranStopTime/1000 : circuit->commandTRAN.stepTime;//Tran time set

    nodeNum = circuit->node_num;
    bTypeDeviceCounter = 0;
    bTypeDeviceNum = 0;//circuit related variables set

    for (auto it = circuit->nodemap.begin();it!=circuit->nodemap.end();it++){
        if(it->second.isGround){
            it->second.id = nodeNum - 1;//ground node id re-set
            break;
        }
    }

    for (int i=0; i < circuit->devices.size(); i++){
        if(circuit->devices[i]->stampType == B_TYPE){
            circuit->devices[i]->bTypeDeviceNo = bTypeDeviceNum;
            bTypeDeviceNum ++;
        }
    }//branch type device number count

    mnaTranInit.set_size(nodeNum+bTypeDeviceNum,nodeNum+bTypeDeviceNum);
    mnaTranInit.zeros();

    rhsTranInit.set_size(nodeNum+bTypeDeviceNum);
    rhsTranInit.zeros();

    mnaTranNext.set_size(nodeNum+bTypeDeviceNum,nodeNum+bTypeDeviceNum);
    mnaTranNext.zeros();

    rhsTranNext.set_size(nodeNum+bTypeDeviceNum);
    rhsTranNext.zeros();

    devicesStampTRAN(true);//initialize must be done before delete ground node

    mnaTranNext.shed_col(nodeNum-1);
    mnaTranNext.shed_row(nodeNum-1);
    rhsTranNext.shed_row(nodeNum-1);//delete ground node

    xTran.set_size(nodeNum+bTypeDeviceNum-1);
    xTran.zeros();

    mnaTranInit.print("nmaTranInit(including ground):");
    rhsTranInit.print("rhsTranInit(including ground):");
    printf("\n");
}

void Analyser::matrixNodeRecordTRAN(ResultRecorder* resultRecorder){
    for (auto it = circuit->commandPlot.nodePlotQueue.begin();it!=circuit->commandPlot.nodePlotQueue.end();it++){
        double yRecord = circuit->nodemap[it->nodeName].isGround? 0 : xTran(circuit->nodemap[it->nodeName].id);
        string description = it->prefix+it->nodeName;
        string yLabel = it->prefix;
        resultRecorder->addRecord(description,"Time(s)",yLabel,tranTime,yRecord);
    }
}