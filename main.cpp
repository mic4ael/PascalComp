#include <iostream>
#include "parser.hpp"

extern int yyparse();

int main()
{
    return yyparse();
}