#ifndef _DEVICE_H_
#define _DEVICE_H_
#include <string>
#include <complex>
#include "../analyser/analyser.h"
#include "../circuit/node.h"

class Analyser;

enum DEVICE_TYPE
{
    G_TYPE=0,//belong to g matrix of mna
    B_TYPE//belong to b matrix of mna
};

class BaseDevice
{
public:
    std::string name;
    DEVICE_TYPE deviceType;

    BaseDevice(){};
    BaseDevice(std::string name,DEVICE_TYPE deviceType): name(name),deviceType(deviceType){};

    virtual void stampDC(Analyser* analyser) = 0;
    virtual void stampAC(Analyser* analyser) = 0;
};

class Vs: virtual public BaseDevice
{
public:
    std::string pos;
    std::string neg;
    double vs_value;
    int bTypeDeviceNo;

    Vs(std::string name,std::string pos,std::string neg,double vs_value)
    : BaseDevice(name,B_TYPE),pos(pos),neg(neg),vs_value(vs_value),bTypeDeviceNo(0){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};


class Resistor: virtual public BaseDevice
{
public:
    std::string pos;
    std::string neg;
    double r_value;

    Resistor(std::string name,std::string pos,std::string neg,double r_value): BaseDevice(name,G_TYPE),pos(pos),neg(neg),r_value(r_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class Capacitor: virtual public BaseDevice
{
public:
    std::string pos;
    std::string neg;
    double c_value;

    Capacitor(std::string name,std::string pos,std::string neg,double c_value): BaseDevice(name,G_TYPE),pos(pos),neg(neg),c_value(c_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class Inductor: virtual public BaseDevice
{
public:
    std::string pos;
    std::string neg;
    double l_value;
    int bTypeDeviceNo;

    Inductor(std::string name,std::string pos,std::string neg,double l_value): BaseDevice(name,B_TYPE),pos(pos),neg(neg),l_value(l_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class VCCS: virtual public BaseDevice
{
    std::string pos;
    std::string neg;
    std::string posC;
    std::string negC;
    double g_value;

    VCCS(std::string name,std::string pos,std::string neg,std::string posC,std::string negC,double g_value): BaseDevice(name,G_TYPE),pos(pos),neg(neg),posC(posC),negC(negC),g_value(g_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};


#endif