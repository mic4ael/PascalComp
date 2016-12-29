#include "codegenerator.hpp"

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
    this->outputFile << "\tmov." << opType << " ";
    if (dst.getSymbolType() == CONSTANT_SYMBOL) {
        this->outputFile << "#" << dst.getSymbolValue().intValue;
    } else {
        this->outputFile << " ";
        if (dst.isSymbolReference())
        {
            this->outputFile << "*BP+" << dst.getAddress();
        }
        else
        {
            this->outputFile << dst.getAddress();
        }
    }

    if (src.isSymbolReference())
    {
        this->outputFile << "," << "*BP+" << src.getAddress();
    }
    else
    {
        this->outputFile << "," << src.getAddress();
    }

    this->outputFile << "\t;mov." << opType << " ";

    if (dst.getSymbolType() == CONSTANT_SYMBOL)
    {
        this->outputFile << dst.getSymbolValue().intValue;
    }
    else
    {
        this->outputFile << dst.getSymbolName();
    }

    this->outputFile << "," << src.getSymbolName() << endl;
}

void CodeGenerator::generateAssignmentStatement()
{
    this->outputFile << "\tmov" << endl;
}

void CodeGenerator::generateWriteStatement(Symbol symbol)
{
    char opType = symbol.getVarType() == INT_TYPE ? 'i' : 'r';
    this->outputFile << "\twrite." << opType << " "
         << symbol.getAddress() << " ";
    this->outputFile << "\t;write." << opType << " "
         << symbol.getSymbolName() << endl;
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
        this->outputFile << "\tadd." << operationType << " " << left.getAddress() << ","
             << right.getAddress() << "," << dst.getAddress()
             << "\t;add." << operationType << " " << left.getSymbolName() << ","
             << right.getSymbolName() << "," << dst.getSymbolName()
             << endl;
        break;
    case '*':
        this->outputFile << "\tmul." << operationType << " " << left.getAddress() << ","
             << right.getAddress() << "," << dst.getAddress()
             << "\t;mul.i " << left.getSymbolName() << "," << right.getSymbolName() << "," << dst.getSymbolName()
             << endl;
        break;
    }
}

void CodeGenerator::generateIntToRealStatement(Symbol src, Symbol dst)
{
    this->outputFile << "\tinttoreal.i " << src.getAddress() << "," << dst.getAddress()
         << "\t;inttoreal.i " << src.getSymbolName() << "," << dst.getSymbolName()
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
    this->outputFile << "\tcall.i #" << procedureName
         << "\t; call.i &" << procedureName
         << endl;
}

void CodeGenerator::generatePushStatement(Symbol symbol)
{
    this->outputFile << "\tpush.i #" << symbol.getAddress();

    if (symbol.isSymbolReference())
    {
        this->outputFile << "\t; push.i &" << symbol.getSymbolName();
    }
    else
    {
        this->outputFile << "\t; push.i #" << symbol.getSymbolName();
    }

    this->outputFile << endl;
}

void CodeGenerator::generateIncSPStatement(int numberOfPushes)
{
    this->outputFile << "\tincsp.i #" << numberOfPushes * 4 << endl;
}

CodeGenerator *codeGenerator = new CodeGenerator();