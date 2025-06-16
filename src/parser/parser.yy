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
%token<s> INDUCTOR CAPACITOR RESISTOR VS VCCS VCVS CS CCVS CCCS DIODE
%token<s> COMMENTLINE
%token<f> VALUE
%type<s> inductor capacitor resistor vccs vs vcvs cs ccvs cccs diode
%type<f> value
%type<s> node modelName
%token END EOL
%token<s> VAR_V VAR_I
%token<s> RK_OP RK_AC RK_DC RK_TRAN RK_DEC RK_OCT RK_LIN
%token<s> RK_PULSE RK_SIN
%token CMD_PRINT CMD_OP CMD_DC CMD_AC CMD_PLOT CMD_OPTION CMD_TRAN

%token<str> LBRACKET
%token<str> RBRACKET

%{
#include <cstdio>
#include "../circuit/circuit.h"
#include "../devices/all_device.h"
#include "../spice_command/command_plot.h"

    extern int yylineno;
    extern int r_number;
    extern int c_number;
    extern int l_number;
    extern int vsrc_number;


    extern std::vector<char* > node_list;
    extern void node_add(char node_name[]);
    extern int node_number ;
    extern int parser_node_id_counter ;

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
        circuit->nodemap[node_name].id = parser_node_id_counter;
        
        parser_node_id_counter ++;
        circuit->node_num ++;
    }
}

bool checkName(std::string device_name)
{
    if (circuit->namemap.find(device_name) != circuit->namemap.end()) {
        return false;
    } else {
        circuit->namemap[device_name] = circuit->device_num;
        circuit->device_num ++;
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

Vs* vsource_d;

void ParseVs(char const *name, char const *node1, char const *node2, double value1, double value2)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2);
    vsource_d = new Vs(name, node1, node2, value1, value2);
    circuit->devices.push_back(vsource_d);
}

Cs* csource_d;

void ParseCs(char const *name, char const *node1, char const *node2, double value1, double value2)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2);
    csource_d = new Cs(name, node1, node2, value1, value2);
    circuit->devices.push_back(csource_d);
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

void ParseDiode(char const *name, char const *node1, char const *node2, char const *model)
{
    if (!checkName(name)) return;
    addNode(node1); addNode(node2);
    Diode* d = new Diode(name, model, node1, node2);
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
         | diode
;

command: print
        | dc
        | ac
        | tran
        | op
        | plot
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

vs: VS node node
        {
            ParseVs($1, $2, $3, 0, 0);
            printf("[VS Line] Name(%s) N+(%s) N-(%s) val(%e)\n", $1, $2, $3, 0);
            vsrc_number ++;
        }
    |
    VS node node value
        {
            ParseVs($1, $2, $3, $4, $4);
            printf("[VS Line] Name(%s) N+(%s) N-(%s) val(%e)\n", $1, $2, $3, $4);
            vsrc_number ++;
        }
    |
    vs RK_DC value
        {
            vsource_d -> dc_value = $3;
        }
    |
    vs RK_AC value
        {
            vsource_d -> ac_value = $3;
        }
    |
    vs RK_PULSE LBRACKET value value value value value value value RBRACKET
    {
        Pulse newPulse($4, $5, $6, $7, $8, $9, $10, true);
        vsource_d->pulseTRAN = newPulse;
        printf("[SpParser] [Command] Pulse detected!");
    }
    |
    vs RK_SIN LBRACKET value value value value value RBRACKET
    {
        Sin newSin($4, $5, $6, $7, $8,true);
        vsource_d->sinTRAN = newSin;
        printf("[SpParser] [Command] Sin detected!");
    }
    ;
;

vcvs: VCVS node node node node value
    {   
        ParseVcvs($1, $2, $3, $4, $5, $6);
        printf("[VCVS Line] Name(%s) N+(%s) N-(%s) NC+(%s) NC-(%s) val(%f)\n", $1, $2, $3, $4, $5, $6);
        vsrc_number ++;
    }
;

cs: CS node node
        {
            ParseCs($1, $2, $3, 0, 0);
            printf("[VS Line] Name(%s) N+(%s) N-(%s) val(%e)\n", $1, $2, $3, 0);
        }
    |
    CS node node value
        {
            ParseCs($1, $2, $3, $4, $4);
            printf("[VS Line] Name(%s) N+(%s) N-(%s) val(%e)\n", $1, $2, $3, $4);
        }
    |
    cs RK_DC value
        {
            csource_d -> dc_value = $3;
        }
    |
    cs RK_AC value
        {
            csource_d -> ac_value = $3;
        }
    |
    cs RK_PULSE LBRACKET value value value value value value value RBRACKET
    {
        Pulse newPulse($4, $5, $6, $7, $8, $9, $10, true);
        csource_d->pulseTRAN = newPulse;
        printf("[SpParser] [Command] Pulse detected!");
    }
    |
    cs RK_SIN LBRACKET value value value value value RBRACKET
    {
        Sin newSin($4, $5, $6, $7, $8, true);
        csource_d->sinTRAN = newSin;
        printf("[SpParser] [Command] Sin detected!");
    }
    ;
;

cccs: CCCS node node VS value
    {   
        ParseCccs($1, $2, $3, $4, $5);
        printf("[CCCS Line] Name(%s) N+(%s) N-(%s) VS(%s) val(%f)\n", $1, $2, $3, $4, $5);
    }
;

ccvs: CCVS node node VS value
    {   
        ParseCcvs($1, $2, $3, $4, $5);
        printf("[CCVS Line] Name(%s) N+(%s) N-(%s) VS(%s) val(%f)\n", $1, $2, $3, $4, $5);
        vsrc_number ++;
    }
;

diode: DIODE node node modelName
    {
        printf("[DIODE Line] Name(%s) N+(%s) N-(%s) model(%s)\n", $1, $2, $3, $4);
        ParseDiode($1, $2, $3, $4);
    }
;

op: CMD_OP
    {
        printf("[OP Line] OP\n");
        circuit->commandOP.run = 1;
    }
;

dc: CMD_DC
    {

    }
    | dc VS value value value 
    {
        printf("[DC Line] node(%s) start(%f) end(%f) step(%f)\n", $2, $3, $4, $5);
        circuit->commandDC.sourceName = $2;
        circuit->commandDC.startValue = $3;
        circuit->commandDC.endValue = $4;
        circuit->commandDC.stepValue = $5;
        circuit->commandDC.run = 1;
    }
    | dc CS value value value 
    {
        printf("[DC Line] node(%s) start(%f) end(%f) step(%f)\n", $2, $3, $4, $5);
        circuit->commandDC.sourceName = $2;
        circuit->commandDC.startValue = $3;
        circuit->commandDC.endValue = $4;
        circuit->commandDC.stepValue = $5;
        circuit->commandDC.run = 1;
    }
;

ac: CMD_AC RK_DEC value value value
    {
        printf("[AC Line]:DEC numPerDec(%d) startFreq(%f) stopFreq(%f)\n", $3, $4, $5);
        circuit->commandAC.run = 1;
        circuit->commandAC.numPerDec = $3;
        circuit->commandAC.startFreq = $4;
        circuit->commandAC.endFreq = $5;
    }
    |
    CMD_AC RK_LIN value value value
    {
        printf("[AC Line]:LIN numPerLin(%d) startFreq(%f) stopFreq(%f)\n", $3, $4, $5);
        printf("[AC Line]:WARNING: LIN is not supported yet.");
    }
    |
    CMD_AC RK_OCT value value value
    {
        printf("[AC Line]:OCT numPerOct(%d) startFreq(%f) stopFreq(%f)\n", $3, $4, $5);
        printf("[AC Line]:WARNING: OCT is not supported yet.");
    }
;

tran:
    CMD_TRAN value { 
        printf("[TRAN Line]:STOPTIME(%f)\n", $2);
        circuit->commandTRAN.run = 1;
        circuit->commandTRAN.stopTime = $2;
        circuit->commandTRAN.stepTime = -1;
    }
    |
    CMD_TRAN value value { 
        printf("[TRAN Line]");
        circuit->commandTRAN.run = 1;
        circuit->commandTRAN.stepTime = $2;
        circuit->commandTRAN.stopTime = $3;
    }
    |
    CMD_TRAN value value value { 
        printf("[TRAN Line]");
        circuit->commandTRAN.run = 1;
        circuit->commandTRAN.stepTime = $2;
        circuit->commandTRAN.stopTime = $3;
        circuit->commandTRAN.startTime = $4;
    }
    ;

print: CMD_PRINT RK_AC
    {
    }
    |  CMD_PRINT RK_DC
    {
    }
    |  CMD_PRINT RK_OP
    {
    }
    |  CMD_PRINT RK_TRAN
    {
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

plot: CMD_PLOT RK_AC
    {
    }
    |  CMD_PLOT RK_DC
    {
    }
    |  CMD_PLOT RK_OP
    {
    }
    |  CMD_PLOT RK_TRAN
    {
    }
    |  plot VAR_V
    {
        CommandPlot::NodeToPlot nodeToPlot;
        std::string node = $2;
        nodeToPlot.nodeName = node.substr(2, node.length() - 3);
        nodeToPlot.prefix = "V";
        circuit->commandPlot.plotEnable = 1;
        circuit->commandPlot.nodePlotQueue.push_back(nodeToPlot);
        printf("[PLOT Line] Node(%s)\n",$2);
    }
    |  plot VAR_I
    {
        CommandPlot::NodeToPlot nodeToPlot;
        std::string node = $2;
        nodeToPlot.nodeName = node.substr(2, node.length() - 3);
        nodeToPlot.prefix = "I";
        circuit->commandPlot.plotEnable = 1;
        circuit->commandPlot.nodePlotQueue.push_back(nodeToPlot);
        printf("[PLOT Line] Node(%s)\n",$2);
    }
;

modelName: node
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
    | VCVS        { $$ = strdup($1); node_add($$);}
    | CS          { $$ = strdup($1); node_add($$);}
    | CCCS        { $$ = strdup($1); node_add($$);}
    | CCVS        { $$ = strdup($1); node_add($$);}
    | DIODE       { $$ = strdup($1); node_add($$);}
    
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
