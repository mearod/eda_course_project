#include <string>
#include <unordered_map>
#include <iostream>
#include "circuit.h"


Circuit::Circuit() {
    node_num = 0;
}

void Circuit::debug_display(){ 
    std::cout<<"node num:"<<this->node_num<<std::endl;
    std::cout<<"node list:"<<std::endl;
    for (auto it = nodemap.begin(); it != nodemap.end(); ++it){
        std::cout << "node name: " << it->first << ", id: " << it->second.id <<",ground:"<<it->second.isGround<< std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"device list:"<<std::endl;
    for (auto it = namemap.begin(); it != namemap.end(); ++it){
        std::cout << "device name: " << it->first << std::endl;
    }
};


Circuit::~Circuit() {
    for (int i = 0;i < devices.size();i++){
        std::cout<<i;
        delete devices[i];
    }
}
