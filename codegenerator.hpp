#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "symbol.hpp"

using namespace std;


class CodeGenerator
{
private:
    stringstream output;
    ofstream outputFile;
    int numberOfPushes;

public:
    CodeGenerator();
    ~CodeGenerator();

    void generateExitStatement();
    void generateJumpStatement(string labelName);
    void generateLabelStatement(string labelName);
    void generateMovStatement(Symbol src, Symbol dst, VarType varType);
    void generateAssignmentStatement();
    void generateWriteStatement(Symbol symbol);
    void generateReadStatement();
    void generateArithmeticStatement(Symbol left, Symbol right, Symbol dst, char op);
    void generateIntToRealStatement(Symbol src, Symbol dst);
    void generateRealToIntStatement(Symbol src, Symbol dst);
    void generateProcedureEnterStatement(string func, int numberOfArguments);
    void generateEnterPlaceholder(string func);
    void generateSubProgramReturnStatements();
    void generateCallStatement(string procedureName);
    void generatePushStatement(Symbol symbol);
    void generateIncSPStatement();
    int getNumberOfPushes() {return this->numberOfPushes;}
    void generateJumpLessStatement(Symbol left, Symbol right, Symbol label);
    void generateJumpGreaterStatement(Symbol left, Symbol right, Symbol label);
    void generateJumpEqualStatement(Symbol left, Symbol right, Symbol label);
    void generateAndStatement(Symbol left, Symbol right, Symbol to);
    void generateOrStatement(Symbol left, Symbol right, Symbol to);
};

#endif