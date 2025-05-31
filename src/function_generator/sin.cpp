#include "function_generator.h"
#include <cmath>

double Sin::getSinValue(double t)
{
    if (t <= tdelay)
        return v0;
    t -= tdelay;
    double period = 1/freq;
    int p = floor(t / period);
    double t0 = t - p * period;
    return std::exp(-t*theta) * va * std::sin(2*M_PI*(t0/period));
}