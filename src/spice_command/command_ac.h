#ifndef _COMMAND_AC_H_
#define _COMMAND_AC_H_
#include <string>
#include <vector>
using namespace std;

class CommandAC
{
public:
    int numPerDec;
    double startFreq;
    double endFreq;
    bool run;

    CommandAC(): numPerDec(0), startFreq(0), endFreq(0), run(0) {}
    CommandAC(int numPerDec, double startFreq, double endFreq, bool run):
        numPerDec(numPerDec), startFreq(startFreq), endFreq(endFreq), run(run) {}
};

#endif