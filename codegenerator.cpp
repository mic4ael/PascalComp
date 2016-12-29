#include "codegenerator.hpp"

CodeGenerator::CodeGenerator()
{

}

void CodeGenerator::generateExitStatement()
{
    cout << "\texit" << endl;
}

void CodeGenerator::generateJumpStatement(string labelName)
{
    cout << "\tjump.i #" << labelName << endl;
}

void CodeGenerator::generateLabelStatement(string labelName)
{
    cout << labelName << ":" << endl;
}

void CodeGenerator::generateMovStatement(Symbol src, Symbol dst, VarType varType)
{
    char opType = varType == INT_TYPE ? 'i' : 'r';
    cout << "\tmov." << opType << " ";
    if (dst.getSymbolType() == CONSTANT_SYMBOL) {
        cout << "#" << dst.getSymbolValue().intValue;
    } else {
        cout << " ";
        if (dst.isSymbolReference())
        {
            cout << "*BP+" << dst.getAddress();
        }
        else
        {
            cout << dst.getAddress();
        }
    }

    if (src.isSymbolReference())
    {
        cout << "," << "*BP+" << src.getAddress();
    }
    else
    {
        cout << "," << src.getAddress();
    }

    cout << "\t;mov." << opType << " ";

    if (dst.getSymbolType() == CONSTANT_SYMBOL)
    {
        cout << dst.getSymbolValue().intValue;
    }
    else
    {
        cout << dst.getSymbolName();
    }

    cout << "," << src.getSymbolName() << endl;
}

void CodeGenerator::generateAssignmentStatement()
{
    cout << "\tmov" << endl;
}

void CodeGenerator::generateWriteStatement(Symbol symbol)
{
    char opType = symbol.getVarType() == INT_TYPE ? 'i' : 'r';
    cout << "\twrite." << opType << " "
         << symbol.getAddress() << " ";
    cout << "\t;write." << opType << " "
         << symbol.getSymbolName() << endl;
}

void CodeGenerator::generateReadStatement()
{
    cout << "\tread" << endl;
}

void CodeGenerator::generateArithmeticStatement(Symbol left, Symbol right, Symbol dst, char op)
{
    char operationType = left.getVarType() == INT_TYPE ? 'i' : 'r';
    switch (op)
    {
    case '+':
        cout << "\tadd." << operationType << " " << left.getAddress() << ","
             << right.getAddress() << "," << dst.getAddress()
             << "\t;add." << operationType << " " << left.getSymbolName() << ","
             << right.getSymbolName() << "," << dst.getSymbolName()
             << endl;
        break;
    case '*':
        cout << "\tmul." << operationType << " " << left.getAddress() << ","
             << right.getAddress() << "," << dst.getAddress()
             << "\t;mul.i " << left.getSymbolName() << "," << right.getSymbolName() << "," << dst.getSymbolName()
             << endl;
        break;
    }
}

void CodeGenerator::generateIntToRealStatement(Symbol src, Symbol dst)
{
    cout << "\tinttoreal.i " << src.getAddress() << "," << dst.getAddress()
         << "\t;inttoreal.i " << src.getSymbolName() << "," << dst.getSymbolName()
         << endl;
}

void CodeGenerator::generateProcedureEnterStatement(int numberOfArguments)
{
    cout << "\tenter.i #" << 4 * numberOfArguments << endl;
}

void CodeGenerator::generateSubProgramReturnStatements()
{
    cout << "\tleave" << endl
         << "\treturn" << endl;
}

void CodeGenerator::generateCallStatement(string procedureName)
{
    cout << "\tcall.i #" << procedureName
         << "\t; call.i &" << procedureName
         << endl;
}

void CodeGenerator::generatePushStatement(Symbol symbol)
{
    cout << "\tpush.i #" << symbol.getAddress();

    if (symbol.isSymbolReference())
    {
        cout << "\t; push.i &" << symbol.getSymbolName();
    }
    else
    {
        cout << "\t; push.i #" << symbol.getSymbolName();
    }

    cout << endl;
}

void CodeGenerator::generateIncSPStatement(int numberOfPushes)
{
    cout << "\tincsp.i #" << numberOfPushes * 4 << endl;
}

CodeGenerator *codeGenerator = new CodeGenerator();