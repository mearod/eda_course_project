#ifndef NONLINEAR_DEVICE_H
#define NONLINEAR_DEVICE_H

#include <string>
#include <complex>
#include "device.h"

class Analyser;
class BaseDevice;

class NonlinearDevice : virtual public BaseDevice {
public:
    NonlinearDevice(){};

    virtual void stampIteration(Analyser* analyser,bool isFirstStamp = 0) = 0;
    virtual void NonlinearValueIteration(Analyser* analyser) = 0;
    virtual bool checkConvergence() = 0;
};

class Diode : public NonlinearDevice 
{
private:
    double lastId;
    double lastVd;
public:
    Diode(std::string name,std::string model,std::string pos, std::string neg, double Vd=1, double Is=1e-12, double Vt=0.025); 
    ~Diode();

    std::string model;

    std::string pos;
    std::string neg;

    double Id;
    double Vd;

    double Is;
    double Vt;//parameters for diode equation

    void stampDC(Analyser* analyser);
    void stampAC(Analyser* analyser);
    void stampTRAN(Analyser* analyser,bool initFlag);

    void stampIteration(Analyser* analyser,bool isFirstStamp);

    double getIDC(Analyser* analyser);
    complex<double> getIAC(Analyser* analyser);
    double getITRAN(Analyser* analyser);

    bool checkConvergence();
    void NonlinearValueIteration(Analyser* analyser);
};

#endif