#ifndef _DEVICE_H_
#define _DEVICE_H_
#include <string>
#include <complex>
#include "../analyser/analyser.h"
#include "../circuit/node.h"

class Analyser;
class Circuit;

enum DEVICE_TYPE
{
    G_TYPE=0,//每次stamp不创建矩阵分支
    B_TYPE//每次stamp涉及新的矩阵分支
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

class BTypeDevice: virtual public BaseDevice
{
public:
    int bTypeDeviceNo;

    BTypeDevice(std::string name): BaseDevice(name,B_TYPE),bTypeDeviceNo(0){};

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

class Inductor: virtual public BTypeDevice
{
public:
    std::string pos;
    std::string neg;
    double l_value;

    Inductor(std::string name,std::string pos,std::string neg,double l_value): BaseDevice(name,B_TYPE),BTypeDevice(name),pos(pos),neg(neg),l_value(l_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class Vccs: virtual public BaseDevice
{
public:
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

class Ccvs: virtual public BTypeDevice
{
private:
    bool findVs(Circuit* circuit);

    std::string posC;
    std::string negC;
    
    int vsBTypeDeviceNo;

public:
    std::string pos;
    std::string neg;
    std::string vsName;
    double ccvs_value;

    Ccvs(std::string name,std::string pos,std::string neg,std::string vsName,double ccvs_value)
    : BaseDevice(name,B_TYPE),BTypeDevice(name),pos(pos),neg(neg),vsName(vsName),ccvs_value(ccvs_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class Vs: public BTypeDevice
{
public:
    std::string pos;
    std::string neg;
    double dc_value;
    double ac_value;

    Vs(std::string name,std::string pos,std::string neg,double dc_value,double ac_value)
    : BaseDevice(name, B_TYPE),BTypeDevice(name),pos(pos),neg(neg),dc_value(dc_value),ac_value(ac_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class Vcvs: virtual public BTypeDevice
{
public:
    std::string pos;
    std::string neg;
    std::string posC;
    std::string negC;
    double vcvs_value;

    Vcvs(std::string name,std::string pos,std::string neg,std::string posC,std::string negC,double vcvs_value)
    : BaseDevice(name,B_TYPE),BTypeDevice(name),pos(pos),neg(neg),posC(posC),negC(negC),vcvs_value(vcvs_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class Cccs: virtual public BaseDevice
{
private:
    bool findVs(Circuit* circuit);

    std::string posC;
    std::string negC;

    int vsBTypeDeviceNo;

public:
    std::string pos;
    std::string neg;
    std::string vsName;

    double cccs_value;

    Cccs(std::string name,std::string pos,std::string neg,std::string vsName,double cccs_value)
    : BaseDevice(name,G_TYPE),pos(pos),neg(neg),vsName(vsName),cccs_value(cccs_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

class Cs: virtual public BaseDevice
{
public:
    std::string pos;
    std::string neg;
    double cs_value;

    Cs(std::string name,std::string pos,std::string neg,double cs_value)
    : BaseDevice(name,G_TYPE),pos(pos),neg(neg),cs_value(cs_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
};

#endif