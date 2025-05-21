#include "parser/parser.hpp"
#include <iostream>
#include <vector>
#include "circuit/circuit.h"
#include "analyser/analyser.h"

extern FILE *yyin;

void callNetlistParser(const char *fileName);

static void device_static();

int r_number = 0;
int c_number = 0;
int l_number = 0;
int vsrc_number = 0;

int device_number = 0;

std::vector<char* > node_list;
void node_add(char node_name[]);
int node_number = 0;


Circuit* circuit;

int main(int argc, char **args)
{
    if (argc != 2) {
        std::cout << "Require argument (netlist)." << std::endl;
        std::cout << "Usage: ./demo netlist" << std::endl;
        exit(1);
    }

    char *fileName = args[1];

    circuit = new Circuit;

    callNetlistParser(fileName);

    Analyser* analyser = new Analyser(circuit);

    analyser->analyseDC();
    
    device_static();

    return 0;
}

static void device_static(){
    device_number = r_number + c_number + l_number;
    std::cout << "#Device: "<<device_number<<"\n"
    <<"#R: "<<r_number<<"   #C:"<<c_number<<"   #L:"<<l_number<<"\n"
    <<"#Vsrc: "<<vsrc_number<<"\n"
    <<"#Node: "<<node_number<<"\n";

    circuit->debug_display();
}

void node_add(char node_name[]){
    for(int i = 0;i<node_list.size();i++)
    {
        if(strcmp(node_name,node_list[i]) == 0) {return;};
    }
    std::cout<<node_name[0]<<std::endl;
    node_number ++;
    node_list.push_back(node_name);
}

void callNetlistParser(const char *fileName)
{
    yyin = fopen(fileName, "r");
    if (!yyin) {
        printf("Can not open %s.\n", fileName);
        exit(1);
    }

    // read title and move the pointer to second line
    char title[128];
    fgets(title, 128, yyin);
    printf("Title: %s", title);

    circuit->title = title;

    int   ret = yyparse();
    if (ret != 0) {
        printf("Parse %s failed.\n", fileName);
        exit(1);
    }

    fclose(yyin);
}