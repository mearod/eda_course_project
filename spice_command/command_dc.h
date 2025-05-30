#ifndef _COMMAND_DC_H_
#define _COMMAND_DC_H_
#include <string>
#include <vector>
using namespace std;

class CommandDC
{
public:
    string sourceName;
    double startValue;
    double endValue;
    double stepValue;
    bool run;

    CommandDC() : sourceName(""), startValue(0), endValue(0), stepValue(0), run(0) {}
    CommandDC(string sourceName, double startValue, double endValue, double stepValue, bool run):
        sourceName(sourceName), startValue(startValue), endValue(endValue), stepValue(stepValue), run(run){}
};

#endif