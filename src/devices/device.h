#ifndef _DEVICE_H_
#define _DEVICE_H_
#include <string>
#include <complex>
#include "../analyser/analyser.h"
#include "../circuit/node.h"
#include "../function_generator/function_generator.h"

using namespace std;
class Analyser;
class Circuit;

enum STAMP_TYPE
{
    G_TYPE=0,//每次stamp不创建矩阵分支
    B_TYPE//每次stamp涉及新的矩阵分支
};

enum TYPE
{
    VSOURCE=1,
    ISOURCE,
    R,C,L,CONTROL_SOURCE,D
};

class BaseDevice
{
public:
    string name;
    STAMP_TYPE stampType;
    TYPE type;
    bool isNonLinearDevice;
    int bTypeDeviceNo;

    BaseDevice(){};
    BaseDevice(string name,STAMP_TYPE stampType,TYPE type,bool isNonLinearDevice): name(name),stampType(stampType),type(type),isNonLinearDevice(isNonLinearDevice){};

    virtual void valueUpdate(double value){};

    virtual void stampDC(Analyser* analyser) = 0;
    virtual void stampAC(Analyser* analyser) = 0;
    virtual void stampTRAN(Analyser* analyser,bool initFlag) = 0;

    virtual double getIDC(Analyser* analyser) = 0;
    virtual complex<double> getIAC(Analyser* analyser) = 0;
    virtual double getITRAN(Analyser* analyser) = 0;
};


class Resistor: virtual public BaseDevice
{
public:
    string pos;
    string neg;
    double r_value;

    Resistor(string name,string pos,string neg,double r_value): BaseDevice(name,G_TYPE,R,false),pos(pos),neg(neg),r_value(r_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
    void stampTRAN(Analyser* analyser,bool initFlag);

    double getIDC(Analyser* analyser);
    complex<double> getIAC(Analyser* analyser);
    double getITRAN(Analyser* analyser);
};


class Vccs: virtual public BaseDevice
{
public:
    string pos;
    string neg;
    string posC;
    string negC;
    double g_value;

    Vccs(string name,string pos,string neg,string posC,string negC,double g_value)
    : BaseDevice(name,G_TYPE,CONTROL_SOURCE,false),pos(pos),neg(neg),posC(posC),negC(negC),g_value(g_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
    void stampTRAN(Analyser* analyser,bool initFlag);

    double getIDC(Analyser* analyser);
    complex<double> getIAC(Analyser* analyser);
    double getITRAN(Analyser* analyser);
};

class Ccvs: virtual public BaseDevice
{
private:
    bool findVs(Circuit* circuit);

    string posC;
    string negC;
    
    int vsBTypeDeviceNo;

public:
    string pos;
    string neg;
    string vsName;
    double ccvs_value;

    Ccvs(string name,string pos,string neg,string vsName,double ccvs_value)
    : BaseDevice(name,B_TYPE,CONTROL_SOURCE,false),pos(pos),neg(neg),vsName(vsName),ccvs_value(ccvs_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
    void stampTRAN(Analyser* analyser,bool initFlag);

    double getIDC(Analyser* analyser);
    complex<double> getIAC(Analyser* analyser);
    double getITRAN(Analyser* analyser);
};

class Vs: virtual public BaseDevice
{
public:
    string pos;
    string neg;
    double dc_value;
    double ac_value;

    Pulse pulseTRAN;
    Sin sinTRAN;

    Vs(string name,string pos,string neg,double dc_value,double ac_value)
    : BaseDevice(name, B_TYPE,VSOURCE,false),pos(pos),neg(neg),dc_value(dc_value),ac_value(ac_value){};

    void valueUpdate(double value){dc_value = value;ac_value = value;};
    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
    void stampTRAN(Analyser* analyser,bool initFlag);

    double getIDC(Analyser* analyser);
    complex<double> getIAC(Analyser* analyser);
    double getITRAN(Analyser* analyser);
};

class Vcvs: virtual public BaseDevice
{
public:
    string pos;
    string neg;
    string posC;
    string negC;
    double vcvs_value;

    Vcvs(string name,string pos,string neg,string posC,string negC,double vcvs_value)
    : BaseDevice(name,B_TYPE,CONTROL_SOURCE,false),pos(pos),neg(neg),posC(posC),negC(negC),vcvs_value(vcvs_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
    void stampTRAN(Analyser* analyser,bool initFlag);

    double getIDC(Analyser* analyser);
    complex<double> getIAC(Analyser* analyser);
    double getITRAN(Analyser* analyser);
};

class Cccs: virtual public BaseDevice
{
private:
    bool findVs(Circuit* circuit);

    string posC;
    string negC;

    int vsBTypeDeviceNo;

public:
    string pos;
    string neg;
    string vsName;

    double cccs_value;

    Cccs(string name,string pos,string neg,string vsName,double cccs_value)
    : BaseDevice(name,G_TYPE,CONTROL_SOURCE,false),pos(pos),neg(neg),vsName(vsName),cccs_value(cccs_value){};

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
    void stampTRAN(Analyser* analyser,bool initFlag);

    double getIDC(Analyser* analyser);
    complex<double> getIAC(Analyser* analyser);
    double getITRAN(Analyser* analyser);
};

class Cs: virtual public BaseDevice
{
public:
    string pos;
    string neg;
    double dc_value;
    double ac_value;

    Pulse pulseTRAN;
    Sin sinTRAN;

    Cs(string name,string pos,string neg,double dc_value,double ac_value)
    : BaseDevice(name,G_TYPE,ISOURCE,false),pos(pos),neg(neg),dc_value(dc_value),ac_value(ac_value){};

    void valueUpdate(double value){dc_value = value;ac_value = value;};
    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
    void stampTRAN(Analyser* analyser,bool initFlag);

    double getIDC(Analyser* analyser);
    complex<double> getIAC(Analyser* analyser);
    double getITRAN(Analyser* analyser);
};

#endif