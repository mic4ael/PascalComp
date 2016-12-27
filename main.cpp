#include <iostream>
#include "parser.hpp"
#include "codegenerator.hpp"
#include "symboltable.hpp"
#include "symbol.hpp"

extern int yyparse();
extern CodeGenerator *codeGenerator;
extern SymbolTable *symbolTable;

int main()
{
    int parseResult = yyparse();

    cout << symbolTable->tableStr() << endl;

    delete codeGenerator;
    delete symbolTable;

    return parseResult;
}