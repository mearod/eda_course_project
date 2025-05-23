#ifndef _CIRCURT_H_
#define _CIRCURT_H_
#include <string>
#include <vector>
#include <armadillo>
#include <unordered_map>
#include "../analyser/analyser.h"
#include "../devices/device.h"

class BaseDevice;

class Circuit
{
private:

public:
    std::string title;

    int node_num;

    struct Node{
        int number;
        int id;
        bool isGround;
    };

    std::unordered_map<std::string, Node> nodemap;//节点名称字典
    std::unordered_map<std::string, int> namemap;//器件名称字典

    std::vector<BaseDevice*> devices;//器件列表


public:
    void debug_display();//debug用展示函数

    Circuit();

    ~Circuit();
};

#endif