#include <string>
#include <unordered_map>
#include <iostream>
#include "circuit.h"


Circuit::Circuit() {
    node_num = 0;
}

void Circuit::debug_display(){ 
    std::cout<<"node num:"<<this->node_num<<std::endl;
    for (auto it = nodemap.begin(); it != nodemap.end(); ++it){
        std::cout << "Key: " << it->first << ", id: " << it->second.id <<",ground:"<<it->second.isGround<< std::endl;
    }
    for (auto it = namemap.begin(); it != namemap.end(); ++it){
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }
};


void Circuit::stampDC(){ 

};

Circuit::~Circuit() {
    for (int i = 0;i < devices.size();i++){
        delete devices[i];
    }
}
