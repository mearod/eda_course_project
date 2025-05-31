#ifndef COMMAND_TRAN_H
#define COMMAND_TRAN_H

#include <string>
#include <vector>

class CommandTRAN
{
public:
    double stopTime;
    double stepTime;
    double startTime;
    bool run;

    CommandTRAN(): stopTime(0), stepTime(0), startTime(0), run(false) {};
    CommandTRAN(double stopTime, double stepTime, double startTime, bool run): stopTime(stopTime), stepTime(stepTime), startTime(startTime), run(run) {};
};

#endif