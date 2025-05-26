#ifndef _RESULT_RECODER_H_
#define _RESULT_RECODER_H_

#include <vector>
#include <string>
using namespace std;

class SingleRecode
{
public:
    struct Point{
        double x;
        double y;
    };
    string nodeName;
    string description;
    vector<Point> recodeData;

    SingleRecode(string nodeName,string description):nodeName(nodeName),description(description) {};
    void pointRecode(double x,double y);
};

class ResultRecoder
{
private:

public:
    int recodesNum;
    vector<SingleRecode*> recodes;

    ResultRecoder();
    ~ResultRecoder();

    int addRecode(string nodeName,string description); //return single recode index;
};

#endif