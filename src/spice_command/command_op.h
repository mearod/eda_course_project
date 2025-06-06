#ifndef COMMAND_OP_H
#define COMMAND_OP_H

#include <string>
#include <vector>
using namespace std;

class CommandOP
{
public:
    bool run;

    CommandOP() :run(0) {}
    CommandOP(bool run):
        run(run){}
};

#endif