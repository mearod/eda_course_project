/* Require bison minimal version */
%require "3.0.4"


/* it will generate a location class which can be used in your lexer */
%locations

%define parse.trace
%define parse.error verbose
%output "parser.cpp"
%verbose

%code requires
{
#include <string.h>
#include <vector>
}



%union
{
    double f;
    int    n;
    char  *s;
};

/* assigning data type for tokens and patterns */
%token<f> FLOAT
%token<s> STRING 
%token<n> INTEGER
%token<s> INDUCTOR CAPACITOR RESISTOR VS VCCS VCVS CS CCVS CCCS
%token<s> COMMENTLINE
%token<f> VALUE
%type<s> inductor capacitor resistor vccs vs vcvs cs ccvs cccs
%type<f> value
%type<s> node
%token END EOL
%token<s> VAR_V VAR_I
%token<s> RK_OP RK_AC RK_DC RK_TRAN
%token<s> CMD_PRINT CMD_OP CMD_DC CMD_AC

%{
#include <cstdio>
#include "../circuit/circuit.h"
#include "../devices/device.h"

    extern int yylineno;
    extern int r_number;
    extern int c_number;
    extern int l_number;
    extern int vsrc_number;


    extern std::vector<char* > node_list;
    extern void node_add(char node_name[]);
    extern int node_number ;
    static int node_id_counter = 0;

    extern Circuit* circuit;


    extern int yylex();

void yyerror(const char* msg){
    printf("error detected at line %d:%s\n",yylineno,msg);
};


void addNode(std::string node_name){
    if (circuit->nodemap.find(node_name) != circuit->nodemap.end()) {
        circuit->nodemap[node_name].number ++;
    } else if (!node_name.compare("0")){
        circuit->nodemap[node_name].isGround = 1;
        circuit->nodemap[node_name].number = 1;
        circuit->nodemap[node_name].id = -1;

        circuit->node_num ++;
    } else{
        circuit->nodemap[node_name].isGround = 0;
        circuit->nodemap[node_name].number = 1;
        circuit->nodemap[node_name].id = node_id_counter;
        
        node_id_counter ++;
        circuit->node_num ++;
    }
}

bool checkName(std::string device_name)
{
    if (circuit->namemap.find(device_name) != circuit->namemap.end()) {
        return false;
    } else {
        circuit->namemap[device_name] = 1;
        return true;
    }
}

void ParseResistor(char const *name, char const *node1, char const *node2, double value)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2);
    Resistor* d = new Resistor(name, node1, node2, value);
    circuit->devices.push_back(d);
}

void ParseInductor(char const *name, char const *node1, char const *node2, double value)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2);
    Inductor* d = new Inductor(name, node1, node2, value);
    circuit->devices.push_back(d);
}

void ParseCapacitor(char const *name, char const *node1, char const *node2, double value)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2);
    Capacitor* d = new Capacitor(name, node1, node2, value);
    circuit->devices.push_back(d);
}

void ParseVs(char const *name, char const *node1, char const *node2, double value)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2);
    Vs* d = new Vs(name, node1, node2, value);
    circuit->devices.push_back(d);
}

void ParseCs(char const *name, char const *node1, char const *node2, double value)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2);
    Cs* d = new Cs(name, node1, node2, value);
    circuit->devices.push_back(d);
}

void ParseVccs(char const *name, char const *node1, char const *node2, char const *node3, char const *node4,double value)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2); addNode(node3); addNode(node4); 
    Vccs* d = new Vccs(name, node1, node2, node3, node4, value);
    circuit->devices.push_back(d);
}

void ParseVcvs(char const *name, char const *node1, char const *node2, char const *node3, char const *node4,double value)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2); addNode(node3); addNode(node4); 
    Vcvs* d = new Vcvs(name, node1, node2, node3, node4, value);
    circuit->devices.push_back(d);
}

void ParseCcvs(char const *name, char const *node1, char const *node2, char const *vc, double value)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2); addNode(vc);
    Ccvs* d = new Ccvs(name, node1, node2, vc, value);
    circuit->devices.push_back(d);
}

void ParseCccs(char const *name, char const *node1, char const *node2, char const *vc, double value)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2); addNode(vc);
    Cccs* d = new Cccs(name, node1, node2, vc, value);
    circuit->devices.push_back(d);
}

%}



%%

spice: netlist end
;

end: end EOL
   | END
;

netlist: netlist line
       | line
;

line: component EOL
    | command EOL
    | EOL
    | error EOL
;

component: resistor
         | capacitor
         | inductor
         | vccs
         | vs
         | vcvs
         | cs
         | cccs
         | ccvs
;

command: print
        | dc
        | op
;


resistor: 
        RESISTOR node node value
        {   
            ParseResistor($1, $2, $3, $4);
            printf("[Resistor Line] Name(%s) N+(%s) N-(%s) val(%e)\n", $1, $2, $3, $4);
            r_number ++;
        }
;

capacitor: CAPACITOR node node value
        {
            ParseCapacitor($1, $2, $3, $4);
            printf("[Capacitor Line] Name(%s) N+(%s) N-(%s) val(%e)\n", $1, $2, $3, $4);
            c_number ++;
        }
;

inductor: INDUCTOR node node value
        {
            ParseInductor($1, $2, $3, $4);
            printf("[Inductor Line] Name(%s) N+(%s) N-(%s) val(%e)\n", $1, $2, $3, $4);
            l_number ++;
        }

;

vccs: VCCS node node node node value
    {   
        ParseVccs($1, $2, $3, $4, $5, $6);
        printf("[VCCS Line] Name(%s) N+(%s) N-(%s) NC+(%s) NC-(%s) val(%f)\n", $1, $2, $3, $4, $5, $6);
    }

;

vs: VS node node value
        {
            ParseVs($1, $2, $3, $4);
            printf("[VS Line] Name(%s) N+(%s) N-(%s) val(%e)\n", $1, $2, $3, $4);
            vsrc_number ++;
        }
;

vcvs: VCVS node node node node value
    {   
        ParseVcvs($1, $2, $3, $4, $5, $6);
        printf("[VCVS Line] Name(%s) N+(%s) N-(%s) NC+(%s) NC-(%s) val(%f)\n", $1, $2, $3, $4, $5, $6);
        vsrc_number ++;
    }
;

cs: CS node node value
    {
        ParseCs($1, $2, $3, $4);
        printf("[CS Line] Name(%s) N+(%s) N-(%s) val(%e)\n", $1, $2, $3, $4);
    }
;

cccs: CCCS node node VS value
    {   
        ParseCccs($1, $2, $3, $4, $5);
        printf("[VCVS Line] Name(%s) N+(%s) N-(%s) VS(%s) val(%f)\n", $1, $2, $3, $4, $5);
    }
;

ccvs: CCVS node node VS value
    {   
        ParseCccs($1, $2, $3, $4, $5);
        printf("[CCVS Line] Name(%s) N+(%s) N-(%s) VS(%s) val(%f)\n", $1, $2, $3, $4, $5);
        vsrc_number ++;
    }
;


op: CMD_OP
    {
        printf("[OP Line] OP\n");
    }
;

dc: CMD_DC
    {

    }
    | dc VS value value value { 
        printf("[DC Line] node(%s) start(%f) end(%f) step(%f)\n", $2, $3, $4, $5);
    }
;

print: CMD_PRINT RK_AC
    {
        //printf("[PRINT Line] AC\n");
    }
    |  CMD_PRINT RK_DC
    {
        //printf("[PRINT Line] DC\n");
    }
    |  CMD_PRINT RK_OP
    {
        //printf("[PRINT Line] OP\n");
    }
    |  CMD_PRINT RK_TRAN
    {
        //printf("[PRINT Line] TRAN\n");
    }
    |  print VAR_V
    {
        printf("[PRINT Line] Node(%s)\n",$2);
    }
    |  print VAR_I
    {
        printf("[PRINT Line] Node(%s)\n",$2);
    }
;


node: STRING
    {
        $$ = new char[strlen($1) + 1];
        strcpy($$, $1);
        $$[strlen($1)] = '\0';
        node_add($$);
    }
    | INTEGER
    {
        char s[30];
        sprintf(s, "%d", $1);
        $$ = new char[strlen(s) + 1];
        strcpy($$, s);
        $$[strlen(s)] = '\0';
        node_add($$);
    }
    | RESISTOR    { $$ = strdup($1); node_add($$);}
    | CAPACITOR   { $$ = strdup($1); node_add($$);}
    | INDUCTOR    { $$ = strdup($1); node_add($$);}
    | VS          { $$ = strdup($1); node_add($$);}
    | VCCS        { $$ = strdup($1); node_add($$);}
;

value: VALUE
     {
        $$ = $1;
     }
     | FLOAT
     {
        $$ = $1;
     }
     | INTEGER
     {
        $$ = $1;
     }
;

%%
