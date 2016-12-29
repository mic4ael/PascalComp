#include "codegenerator.hpp"
#include "symboltable.hpp"

extern SymbolTable *symbolTable;

CodeGenerator::CodeGenerator()
{
    outputFile.open("output.asm");
}

CodeGenerator::~CodeGenerator()
{
    this->outputFile.close();
}

void CodeGenerator::generateExitStatement()
{
    this->outputFile << "\texit" << endl;
}

void CodeGenerator::generateJumpStatement(string labelName)
{
    this->outputFile << "\tjump.i #" << labelName << endl;
}

void CodeGenerator::generateLabelStatement(string labelName)
{
    this->outputFile << labelName << ":" << endl;
}

void CodeGenerator::generateMovStatement(Symbol src, Symbol dst, VarType varType)
{
    char opType = varType == INT_TYPE ? 'i' : 'r';
    this->outputFile << "\tmov." << opType << " " << dst.getASMOperand();
    this->outputFile << "," << src.getASMOperand();
    this->outputFile << endl;
}

void CodeGenerator::generateAssignmentStatement()
{
    this->outputFile << "\tmov" << endl;
}

void CodeGenerator::generateWriteStatement(Symbol symbol)
{
    char opType = symbol.getVarType() == INT_TYPE ? 'i' : 'r';
    this->outputFile << "\twrite." << opType << " "
         << symbol.getASMOperand() << " " << endl;
}

void CodeGenerator::generateReadStatement()
{
    this->outputFile << "\tread" << endl;
}

void CodeGenerator::generateArithmeticStatement(Symbol left, Symbol right, Symbol dst, char op)
{
    char operationType = left.getVarType() == INT_TYPE ? 'i' : 'r';
    switch (op)
    {
    case '+':
        this->outputFile << "\tadd." << operationType << " " << left.getASMOperand() << ","
             << right.getASMOperand() << "," << dst.getASMOperand() << endl;
        break;
    case '*':
        this->outputFile << "\tmul." << operationType << " " << left.getAddress() << ","
                         << right.getAddress() << "," << dst.getAddress() << endl;
        break;
    case '-':
        this->outputFile << "\tsub." << operationType << " " << left.getAddress() << ","
                         << right.getAddress() << "," << dst.getAddress() << endl;
        break;
    }
}

void CodeGenerator::generateIntToRealStatement(Symbol src, Symbol dst)
{
    this->outputFile << "\tinttoreal.i " << src.getASMOperand() << "," << dst.getASMOperand()
         << endl;
}

void CodeGenerator::generateRealToIntStatement(Symbol src, Symbol dst)
{
    this->outputFile << "\trealtoint.r " << src.getAddress() << "," << dst.getAddress()
         << endl;
}

void CodeGenerator::generateProcedureEnterStatement(int numberOfArguments)
{
    this->outputFile << "\tenter.i #" << 4 * numberOfArguments << endl;
}

void CodeGenerator::generateSubProgramReturnStatements()
{
    this->outputFile << "\tleave" << endl
         << "\treturn" << endl;
}

void CodeGenerator::generateCallStatement(string procedureName)
{
    this->outputFile << "\tcall.i #" << procedureName << endl;
}

void CodeGenerator::generatePushStatement(Symbol symbol)
{
    this->numberOfPushes += 1;
    this->outputFile << "\tpush.i #" << symbol.getAddress();
    this->outputFile << endl;
}

void CodeGenerator::generateIncSPStatement()
{
    if (this->numberOfPushes != 0)
    {
        symbolTable->insertConstant(this->numberOfPushes * 4);
        this->outputFile << "\tincsp.i #" << this->numberOfPushes * 4 << endl;
        this->numberOfPushes = 0;
    }
}

CodeGenerator *codeGenerator = new CodeGenerator();