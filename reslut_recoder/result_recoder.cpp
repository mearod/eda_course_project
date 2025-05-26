#include <vector>
#include <string>

#include "result_recoder.h"
using namespace std;

void SingleRecode::pointRecode(double x,double y){
    Point point;
    point.x = x;
    point.y = y;
    recodeData.push_back(point);
}

ResultRecoder::ResultRecoder(){
    recodesNum = 0;
}

ResultRecoder::~ResultRecoder(){
    for(int i =0;i<recodesNum;++i){
        delete recodes[i];
    }
}

int ResultRecoder::addRecode(string nodeName,string description){
    recodesNum ++;
    SingleRecode* newRecode = new SingleRecode(nodeName,description);
    recodes.push_back(newRecode);
    return recodesNum;
}