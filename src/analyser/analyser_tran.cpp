#include "analyser.h"
#include <assert.h>
#include <cmath>
#include <armadillo>

void Analyser::analyseStepTRAN(){
    devicesStampTRAN(false);


    //non-linear part iteration
    mnaIte = arma::cx_mat(mnaTranNext, arma::zeros<arma::mat>(size(mnaTranNext)));
    rhsIte = arma::cx_mat(rhsTranNext, arma::zeros<arma::mat>(size(rhsTranNext)));


    if(!IterationSolve(32))
    {
        logOutput("TRAN iteration failed after 32 times iteration at time "+std::to_string(tranTime)+"s.",true);
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
    xIte = cx_vec(xTran,arma::zeros<arma::vec>(size(xTran)));
    //xTran.print("tran solve result:");
    printf("\n");
}

void Analyser::stepControlTRAN(){
    double stepMinTemp = 1e10;

    for (auto& device : circuit->devices) {
        DynamicDevice* dynamicDevice = dynamic_cast<DynamicDevice*>(device);
        if (dynamicDevice)
        {
            double value = dynamicDevice->filterLTE(this, tranStep);
            stepMinTemp = std::min(stepMinTemp, value);
        }
    }

    tranStep = std::min(tranStepMin, stepMinTemp);
    
}

void Analyser::analyseTRAN(){
    analyseInitTRAN();
    if(tranStepMin<0){
        cout<<"TRAN analyse error: step time cannot be negative."<<std::endl;
        return;
    }
    while(tranTime < tranStopTime){
        analyseStepTRAN();
        matrixNodeRecordTRAN(resultRecorderTRAN);
        stepControlTRAN();
        logOutput("tran step time: "+std::to_string(tranStep*1e9)+"ns.",false);
        TotalStepTRAN ++;
        tranTime += tranStep;
    }
    resultRecorderTRAN->debug_print();
    resultRecorderTRAN->debugPlotAllRecords();
    logOutput("TRAN analyse finished. Total steps: "+std::to_string(TotalStepTRAN)+".",false);
}

void Analyser::analyseInitTRAN(){
    if(checkPlotNodeExists() == false){
        return;
    }
    tranTime = circuit->commandTRAN.startTime;
    tranStopTime = circuit->commandTRAN.stopTime;
    tranStepMin = (circuit->commandTRAN.stepTime < 0) ? tranStopTime/10000 : circuit->commandTRAN.stepTime;//Tran time set
    tranStep    = tranStepMin;

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
        string description = it->prefix+it->nodeName;
        string xLabel = circuit->commandDC.sourceName;
        string yLabel = it->prefix;
        if(it->prefix == "V")
        {
            double yRecord = circuit->nodemap[it->nodeName].isGround? 0 : real(xTran(circuit->nodemap[it->nodeName].id));
            resultRecorder->addRecord(description,"Time(s)",yLabel,tranTime,yRecord);
        }
        else if(it->prefix == "I")
        {   
            double yRecord = circuit->devices[circuit->namemap[it->nodeName]]->getITRAN(this);
            resultRecorder->addRecord(description,"Time(s)",yLabel,tranTime,yRecord);
        }
        else{assert(0);}
    }
}