#ifndef _COMMAND_PLOT_H_
#define _COMMAND_PLOT_H_
#include <string>
#include <vector>
using namespace std;

class CommandPlot
{
public:
    struct NodeToPlot{
        string nodeName;
        string prefix;//V or I
    };

    bool plotEnable;
    vector<NodeToPlot> nodePlotQueue;
};

#endif