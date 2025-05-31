#include "function_generator.h"
#include <cmath>

double Pulse::getPulseValue(double t)
{
    int p = floor(t / period);
    double t0 = t - p * period;
    if (t0 <= tdelay)
        return v1;
    t0 -= tdelay;
    if (t0 <= trise)
        return v1 + t0 / trise * (v2 - v1);
    t0 -= trise;
    if (t0 <= pulseWidth)
        return v2;
    t0 -= pulseWidth;
    if (t0 <= tfall)
        return v2 - t0 / tfall * (v2 - v1);
    return v1;
}

