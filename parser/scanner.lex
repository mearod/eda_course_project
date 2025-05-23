/*******************************************************

Lexer for SPICE Parser Template

Author: Limin Hao, Jiajun Chen, Guoyong Shi

Used for the course project of "Introduction to EDA", 2024

MSDA Lab, SJTU

2024-03-05

*******************************************************/

%option yylineno
%option header-file="scanner.hpp"

%{
#include "parser.hpp"


char *copyStr(const char *str);
double parseValue(const char *str);
%}

/* Defining output file name */
%option outfile="scanner.cpp"


/* Defining regular expressions of the patterns */
ALPHA     [A-Za-z_]
DIGIT     [0-9]
ALPHANUM  [A-Za-z_0-9]
STRING    {ALPHANUM}+
INTEGER   {DIGIT}+
FLOAT     [\-]?{DIGIT}+"."{DIGIT}+([Ee][\+\-]?{DIGIT}+)?

RESISTOR  [Rr]{ALPHANUM}+
CAPACITOR [Cc]{ALPHANUM}+
INDUCTOR  [Ll]{ALPHANUM}+
VS        [Vv]{ALPHANUM}+
VCCS      [Gg]{ALPHANUM}+
VCVS      [Ee]{ALPHANUM}+
CS        [Ii]{ALPHANUM}+
CCVS      [Hh]{ALPHANUM}+
CCCS      [Ff]{ALPHANUM}+

EOL       [\n]
DELIMITER [ \t]+
UNIT      [Ff]|[Pp]|[Nn]|[Mm]|[Kk]|[Mm][Ee][Gg]|[Gg]|[Tt]|[Uu]
VALUE     ({FLOAT}|[\-]?{INTEGER}){UNIT}?
COMMENTLINE   \*.*\n
END       [\.][Ee][Nn][Dd]

VAR_V           [Vv]\({ALPHANUM}+\)
VAR_I           [Ii]\({ALPHANUM}+\)

RK_OP       [Oo][Pp]
RK_TRAN     [Tt][Rr][Aa][Nn]
RK_AC       [Aa][Cc]
RK_DC       [Dd][Cc]

CMD_PRINT     [\.][Pp][Rr][Ii][Nn][Tt]
CMD_OP        [\.][Oo][Pp]
CMD_DC        [\.][Dd][Cc]
CMD_AC        [\.][Aa][Cc]

%%

{CAPACITOR} {yylval.s = copyStr(yytext); return CAPACITOR;}
{INDUCTOR}  {yylval.s = copyStr(yytext); return INDUCTOR;}
{RESISTOR}  {yylval.s = copyStr(yytext); return RESISTOR;}
{VS}      {yylval.s = copyStr(yytext); return VS;  }
{VCCS}      {yylval.s = copyStr(yytext); return VCCS;}
{VCVS}      {yylval.s = copyStr(yytext); return VCVS;}
{CS}      {yylval.s = copyStr(yytext); return CS  ;}
{CCVS}      {yylval.s = copyStr(yytext); return CCVS;}
{CCCS}      {yylval.s = copyStr(yytext); return CCCS;}

{EOL}       {return EOL;}
<<EOF>>     {yyterminate();}
{DELIMITER} {}
{COMMENTLINE}   {}
{END}       {return END;}

{VAR_V}     {yylval.s = copyStr(yytext);return VAR_V;}
{VAR_I}     {yylval.s = copyStr(yytext);return VAR_I;}

{RK_OP}     {return RK_OP;}
{RK_AC}     {return RK_AC;}
{RK_DC}     {return RK_DC;}
{RK_TRAN}    {return RK_TRAN;}

{CMD_PRINT}  {return CMD_PRINT;}
{CMD_DC}    {return CMD_DC;}
{CMD_OP}     {return CMD_OP;}
{CMD_AC}     {return CMD_AC;}

{INTEGER}   {yylval.n = atoi(yytext); return INTEGER;}
{FLOAT}     {yylval.f = atof(yytext); return FLOAT;}
{VALUE}     {yylval.f = parseValue(yytext); return VALUE;}
{STRING}    {yylval.s = copyStr(yytext); return STRING;}

%%

int yywrap() { return 1; }

char *copyStr(const char *str)
{
    char *newStr;
    newStr = (char *)malloc((strlen(str) + 1) * sizeof(char));
    strcpy(newStr, str);
    newStr[strlen(str)] = '\0';
    return newStr;
}

double parseValue(const char *str)
{
    double value = atof(str);
    int    len = strlen(str);

    char u = str[len - 1];
    if (u == 'F' || u == 'f')
        value *= 1e-15;
    else if (u == 'P' || u == 'p')
        value *= 1e-12;
    else if (u == 'N' || u == 'n')
        value *= 1e-9;
    else if (u == 'U' || u == 'u')
        value *= 1e-6;
    else if (u == 'M' || u == 'm')
        value *= 1e-3;
    else if (u == 'K' || u == 'k')
        value *= 1e3;
    else if (u == 'G' || u == 'g') {
        if (str[len - 2] == 'E' || str[len - 2] == 'e')
            value *= 1e6;
        else
            value *= 1e9;
    } else if (u == 'T' || u == 't')
        value *= 1e12;

    return value; 
}