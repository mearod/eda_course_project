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

class Vccs: virtual public BaseDevice
{
    std::string pos;
    std::string neg;
    std::string posC;
    std::string negC;
    double g_value;

    Vccs(std::string name,std::string pos,std::string neg,std::string posC,std::string negC,double g_value)
    : BaseDevice(name,G_TYPE),pos(pos),neg(neg),posC(posC),negC(negC),g_value(g_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class Ccvs: virtual public BaseDevice
{
    std::string pos;
    std::string neg;
    std::string posC;
    std::string negC;
    double ccvs_value;

    Ccvs(std::string name,std::string pos,std::string neg,std::string posC,std::string negC,double ccvs_value)
    : BaseDevice(name,B_TYPE),pos(pos),neg(neg),posC(posC),negC(negC),ccvs_value(ccvs_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
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

class Vcvs: virtual public BaseDevice
{
public:
    std::string pos;
    std::string neg;
    std::string posC;
    std::string negC;
    double vcvs_value;
    int bTypeDeviceNo;

    Vcvs(std::string name,std::string pos,std::string neg,double vcvs_value)
    : BaseDevice(name,B_TYPE),pos(pos),neg(neg),vcvs_value(vcvs_value),bTypeDeviceNo(0){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class Cccs: virtual public BaseDevice
{
public:
    std::string pos;
    std::string neg;
    std::string vsName;
    double cccs_value;
    int bTypeDeviceNo;

    Cccs(std::string name,std::string pos,std::string neg,std::string vsName,double cccs_value)
    : BaseDevice(name,B_TYPE),pos(pos),neg(neg),vsName(vsName),cccs_value(cccs_value),bTypeDeviceNo(0){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class Is: virtual public BaseDevice
{
public:
    std::string pos;
    std::string neg;
    std::string posC;
    std::string negC;
    double is_value;

    Is(std::string name,std::string pos,std::string neg,double is_value)
    : BaseDevice(name,G_TYPE),pos(pos),neg(neg),is_value(is_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

#endif