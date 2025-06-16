#ifndef DYNAMIC_DEVICE_H
#define DYNAMIC_DEVICE_H

#include "device.h"

class DynamicDevice : virtual public BaseDevice {
public:
    DynamicDevice(){};

    virtual double filterLTE(Analyser* analyser, double step) = 0;
};

#endif

class Capacitor: public DynamicDevice
{
private:
    double ILastTranStep;
public:
    string pos;
    string neg;
    double c_value;

    double voltageTRAN;

    Capacitor(string name,string pos,string neg,double c_value): BaseDevice(name,B_TYPE,C,false),DynamicDevice(),pos(pos),neg(neg),c_value(c_value){ILastTranStep = 0;};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
    void stampTRAN(Analyser* analyser,bool initFlag);

    double filterLTE(Analyser* analyser, double step);

    double getIDC(Analyser* analyser);
    complex<double> getIAC(Analyser* analyser);
    double getITRAN(Analyser* analyser);
};

class Inductor: public DynamicDevice
{
private:
    double VLastTranStep;
public:
    string pos;
    string neg;
    double l_value;

    double currentTRAN;

    Inductor(string name,string pos,string neg,double l_value): BaseDevice(name,B_TYPE,L,false),DynamicDevice(),pos(pos),neg(neg),l_value(l_value){VLastTranStep = 0;};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
    void stampTRAN(Analyser* analyser,bool initFlag);

    double filterLTE(Analyser* analyser, double step);

    double getIDC(Analyser* analyser);
    complex<double> getIAC(Analyser* analyser);
    double getITRAN(Analyser* analyser);
};