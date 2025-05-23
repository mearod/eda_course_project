#include "parser/parser.hpp"
#include <iostream>
#include <vector>
#include "circuit/circuit.h"
#include "analyser/analyser.h"

extern FILE *yyin;

int r_number = 0;
int c_number = 0;
int l_number = 0;
int vsrc_number = 0;

std::vector<char* > node_list;
void node_add(char node_name[]);
int node_number = 0;
int parser_node_id_counter = 0;

Circuit* circuit;
Analyser* analyser;

void initializeSimulate();
void endSimulate(char *fileName);

bool callNetlistParser(const char *fileName);

static void device_static();




int startSimulate(char *fileName)
{
    initializeSimulate();

    circuit = new Circuit;

    if(!callNetlistParser(fileName)) {
        std::cout<<"file not found!\n";
        return 0;
    }

    analyser = new Analyser(circuit);

    analyser->analyseDC();
    
    analyser->analyseAC();

    circuit->debug_display();
    //device_static();

    endSimulate(fileName);

    delete analyser;
    //delete circuit;
    

    return 0;
}

void initializeSimulate(){
yyin = NULL;

r_number = 0;
c_number = 0;
l_number = 0;
vsrc_number = 0;

node_number = 0;
parser_node_id_counter = 0;
}

void endSimulate(char *fileName){
    node_list.clear();
    printf("simulation for file %s ends.\n",fileName);
}

static void device_static(){
    std::cout
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
    node_number ++;
    node_list.push_back(node_name);
}

bool callNetlistParser(const char *fileName)
{
    yyin = fopen(fileName, "r");
    printf("%s\n",fileName);
    if (yyin == NULL) {
        printf("Can not open %s.\n", fileName);
        return 0;
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

    return 1;
}