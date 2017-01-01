%option nounput
%option yylineno
%option noyywrap

%{

#include <iostream>
#include "parser.hpp"
#include "symboltable.hpp"
#include "symbol.hpp"

using namespace std;

extern SymbolTable *symbolTable;

%}

NEWLINE "\n"
TAB "\t"
SPACE " "
LETTER [a-zA-Z]
DIGIT [0-9]
INTEGER -?{DIGIT}+
REAL {DIGIT}*\.{DIGIT}+([eE][-+]?{DIGIT}+)?
ID {LETTER}({LETTER}|{DIGIT})*

%%

{SPACE} |
{TAB} |
{NEWLINE} |
"{"[^{]*"}" /* ignore */;

[\(\):;,\[\]] return yytext[0];

"program" return PROGRAM;
"var" return VAR;
"array" return ARRAY;
"of" return OF;
"integer" return INTEGER_TYPE_TOKEN;
"real" return REAL_TYPE_TOKEN;
"function" return FUNCTION;
"procedure" return PROCEDURE;
"begin" return BEGIN_TOKEN;
"end" return END_TOKEN;
"if" return IF;
"then" return THEN;
"else" return ELSE;
"while" return WHILE;
"do" return DO;
"div" return DIV;
"mod" return MOD;
"and" return AND;
"or" return OR;
"not" return NOT;
".." return DOTDOT;
"." return DOT;
"+" return PLUS;
"-" return MINUS;
"/" return DIVISION;
"*" return MULTIPLICATION;
"=" return EQUAL;
"<>" return NOT_EQUAL;
"<" return LESS;
">" return GREATER;
">=" return GREATER_OR_EQUAL;
"<=" return LESS_OR_EQUAL;
":=" return ASSIGN;

{INTEGER} {
    int symbolIndex = symbolTable->lookupSymbol(atoi(yytext));
    if (symbolIndex == -1)
    {
        yylval = symbolTable->insertConstant(atoi(yytext));
    } else {
        yylval = symbolIndex;
    }
    return INTEGER;
}

{REAL} {
    int symbolIndex = symbolTable->lookupSymbol((double) atof(yytext));
    if (symbolIndex == -1)
    {
        yylval = symbolTable->insertDoubleConstant((double) atof(yytext));
    } else {
        yylval = symbolIndex;
    }
    return REAL;
}

{ID} {
    int symbolIndex = symbolTable->lookupSymbol(yytext);
    if (symbolIndex == -1)
    {
        yylval = symbolTable->insertSymbol(yytext);
    } else {
        yylval = symbolIndex;
    }

    return ID;
}

<<EOF>> return 0;

. {
    cout << "Mamy problem. Wykryto niepoprawny znak: " << yytext << endl;
}

%%
