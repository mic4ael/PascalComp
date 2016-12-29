#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include <string>
#include <iostream>

#include "symbol.hpp"

using namespace std;


class CodeGenerator
{
public:
    CodeGenerator();

    void generateExitStatement();
    void generateJumpStatement(string labelName);
    void generateLabelStatement(string labelName);
    void generateMovStatement(Symbol src, Symbol dst, VarType varType);
    void generateAssignmentStatement();
    void generateWriteStatement(Symbol symbol);
    void generateReadStatement();
    void generateArithmeticStatement(Symbol left, Symbol right, Symbol dst, char op);
    void generateIntToRealStatement(Symbol src, Symbol dst);
    void generateProcedureEnterStatement(int numberOfArguments);
    void generateSubProgramReturnStatements();
    void generateCallStatement(string procedureName);
    void generatePushStatement(Symbol symbol);
    void generateIncSPStatement(int numberOfPushes);
};

#endif