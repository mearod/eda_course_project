#ifndef COMMAND_TRAN_H
#define COMMAND_TRAN_H

#include <string>
#include <vector>

class CommandTRAN
{
public:
    double stopTime;
    bool run;

    CommandTRAN(): stopTime(0), run(false) {};
    CommandTRAN(double stopTime, bool run): stopTime(stopTime), run(run) {};
};

#endif