%option nounput
%option yylineno

%{

#include <iostream>
#include <math>
#include "parser.hpp"

using namesapce std;

%}

NEWLINE "\n"
TAB "\t"
SPACE " "
LETTER [a-zA-Z]
DIGIT [0-9]
INTEGER {DIGIT}+
REAL {DIGIT}*"."{DIGIT}+([eE][-+]?{DIGIT}+)?
ID {LETTER}({LETTER}|{DIGIT})*

%%

{SPACE} |
{TAB} |
{NEWLINE} /* ignore */;

"program" return PROGRAM;
"var" return VAR;
"array" return ARRAY;
"of" return OF;

"integer" {
    return INTEGER;
}

"real" {
    return REAL;
}

"function" {
    return FUNCTION;
}

"procedure" {
    return PROCEDURE;
}

"begin" {
    return BEGIN;
}

"end" {
    return END;
}

"if" {
    return IF;
}

"then" {
    return THEN;
}

"else" {
    return ELSE;
}

"while" {
    return WHILE;
}

"do" {
    return DO;
}

"div" {
    return DIV;
}

"mod" {
    return MOD;
}

"and" {
    return AND;
}

"or" {
    return OR;
}

"not" {
    return NOT;
}

".." {
    return DOTDOT;
}

"+" {
    return PLUS;
}

"-" {
    return MINUS;
}

"/" {
    return DIVISION;
}

"*" {
    return MULTIPLY;
}

"=" {
    return EQUAL;
}

"<>" {
    return NOT_EQUAL;
}

"<" {
    return LESS;
}

">" {
    return GREATER;
}

">=" {
    return EORGREATER;
}

"<=" {
    return EORLESS;
}

":=" {
    return ASSIGN;
}

{ID} {
    return ID;
}

<<EOF>> return 0;

. {
    cout << "Mamy problem. Wykryto niepoprawny znak: " << yytext << endl;
}

%%
