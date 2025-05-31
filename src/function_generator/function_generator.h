#ifndef FUNCTION_GENERATOR_H
#define FUNCTION_GENERATOR_H

class Pulse {
public:
    double v1;
    double v2;
    double tdelay;
    double trise;
    double tfall;
    double pulseWidth;
    double period;

    bool enabled;

    Pulse(
        double v1,
        double v2,
        double tdelay,
        double trise,
        double tfall,
        double pulseWidth,
        double period,
        bool enabled
    ): v1(v1), v2(v2), tdelay(tdelay), trise(trise), tfall(tfall), pulseWidth(pulseWidth), period(period), enabled(enabled) {} 

    Pulse(): v1(0), v2(0), tdelay(0), trise(0), tfall(0), pulseWidth(0), period(0), enabled(false) {} 
    
    double getPulseValue(double t);
};

class Sin {
public:
    double v0;
    double va;
    double freq;
    double tdelay;
    double theta;

    bool enabled;

    Sin(
        double v0,
        double va,
        double freq,
        double tdelay,
        double theta,
        bool enabled
    ): v0(v0), va(va), freq(freq), tdelay(tdelay), theta(theta), enabled(enabled) {} 

    Sin(): v0(0), va(0), freq(0), tdelay(0), theta(0), enabled(false) {} 

    double getSinValue(double t);
};
#endif