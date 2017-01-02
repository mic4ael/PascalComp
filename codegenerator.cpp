#include "codegenerator.hpp"
#include "symboltable.hpp"

extern SymbolTable *symbolTable;

CodeGenerator::CodeGenerator()
{
    this->outputFile.open("output.asm");
}

CodeGenerator::~CodeGenerator()
{
    this->outputFile << this->output.str();
    this->outputFile.close();
}

void CodeGenerator::generateExitStatement()
{
    this->output << "\texit" << endl;
}

void CodeGenerator::generateJumpStatement(string labelName)
{
    this->output << "\tjump.i #" << labelName << endl;
}

void CodeGenerator::generateLabelStatement(string labelName)
{
    this->output << labelName << ":" << endl;
}

void CodeGenerator::generateMovStatement(Symbol src, Symbol dst, VarType varType)
{
    char opType = varType == INT_TYPE ? 'i' : 'r';
    this->output << "\tmov." << opType << " " << dst.getASMOperand();
    this->output << ",";
    if (src.getVarType() == ARRAY_INT_TYPE || src.getVarType() == ARRAY_REAL_TYPE)
        this->output << "*";
    this->output << src.getASMOperand();
    this->output << endl;
}

void CodeGenerator::generateAssignmentStatement()
{
    this->output << "\tmov" << endl;
}

void CodeGenerator::generateWriteStatement(Symbol symbol)
{
    char opType = symbol.getVarType() == INT_TYPE ? 'i' : 'r';
    this->output << "\twrite." << opType << " "
                     << symbol.getASMOperand() << " " << endl;
}

void CodeGenerator::generateReadStatement(Symbol symbol)
{
    this->output << "\tread.i " << symbol.getASMOperand() << endl;
}

void CodeGenerator::generateArithmeticStatement(Symbol left, Symbol right, Symbol dst, char op)
{
    char operationType = left.getVarType() == INT_TYPE || left.getVarType() == ARRAY_INT_TYPE ? 'i' : 'r';
    switch (op)
    {
    case '+':
        this->output << "\tadd." << operationType << " " << left.getASMOperand() << ","
             << right.getASMOperand() << "," << dst.getASMOperand() << endl;
        break;
    case '*':
        this->output << "\tmul." << operationType << " " << left.getASMOperand() << ","
                         << right.getASMOperand() << "," << dst.getASMOperand() << endl;
        break;
    case '-':
        this->output << "\tsub." << operationType << " " << left.getASMOperand() << ","
                     << right.getASMOperand() << "," << dst.getASMOperand() << endl;
        break;
    case '/':
        this->output << "\tdiv." << operationType << " " << left.getASMOperand() << ","
                         << right.getASMOperand() << "," << dst.getASMOperand() << endl;
        break;
    }
}

void CodeGenerator::generateDivStatement(Symbol left, Symbol right, Symbol dst)
{
    char operationType = left.getVarType() == INT_TYPE ? 'i' : 'r';
    this->output << "\tdiv." << operationType << " " << left.getASMOperand() << ","
                 << right.getASMOperand() << "," << dst.getASMOperand() << endl;
}

void CodeGenerator::generateModStatement(Symbol left, Symbol right, Symbol dst)
{
    char operationType = left.getVarType() == INT_TYPE ? 'i' : 'r';
    this->output << "\tmod." << operationType << " " << left.getASMOperand() << ","
                 << right.getASMOperand() << "," << dst.getASMOperand() << endl;
}

void CodeGenerator::generateIntToRealStatement(Symbol src, Symbol dst)
{
    this->output << "\tinttoreal.i " << src.getASMOperand() << "," << dst.getASMOperand()
                 << endl;
}

void CodeGenerator::generateRealToIntStatement(Symbol src, Symbol dst)
{
    this->output << "\trealtoint.r " << src.getASMOperand() << "," << dst.getASMOperand()
                 << endl;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void CodeGenerator::generateProcedureEnterStatement(string func, int num)
{
    string s("$enter-" + func);
    string tmp(this->output.str());
    replace(tmp, s, "enter.i #" + std::to_string(num));
    this->output.str("");
    this->output << tmp;
}

void CodeGenerator::generateEnterPlaceholder(string func)
{
    this->output << "\t$enter-" << func << endl;
}

void CodeGenerator::generateSubProgramReturnStatements()
{
    this->output << "\tleave" << endl
                 << "\treturn" << endl;
}

void CodeGenerator::generateCallStatement(string procedureName)
{
    this->output << "\tcall.i #" << procedureName << endl;
}

void CodeGenerator::generatePushStatement(Symbol symbol)
{
    this->numberOfPushes += 1;
    this->output << "\tpush.i ";
    if (symbol.getSymbolType() != ARGUMENT_SYMBOL && symbol.getVarType() != ARRAY_INT_TYPE && symbol.getVarType() != ARRAY_REAL_TYPE)
        this->output << "#";
    this->output << symbol.getASMOperand(true);
    this->output << endl;
}

void CodeGenerator::generateIncSPStatement()
{
    if (this->numberOfPushes != 0)
    {
        symbolTable->insertConstant(this->numberOfPushes * 4);
        this->output << "\tincsp.i #" << this->numberOfPushes * 4 << endl;
        this->numberOfPushes = 0;
    }
}

void CodeGenerator::generateJumpLessStatement(Symbol left, Symbol right, Symbol label)
{
    if (left.getVarType() == right.getVarType())
    {
        if (left.getVarType() == INT_TYPE)
        {
            this->output << "\tjl.i " << left.getASMOperand() << ","
                         << right.getASMOperand() << ",#" << label.getSymbolName()
                         << endl;
        }
    }
}

void CodeGenerator::generateJumpEqualStatement(Symbol left, Symbol right, Symbol label)
{
    this->output << "\tje.i " << left.getASMOperand() << ","
                 << right.getASMOperand() << ",#" << label.getSymbolName()
                 << endl;
}


void CodeGenerator::generateAndStatement(Symbol left, Symbol right, Symbol to)
{
    this->output << "\tand.i " << left.getASMOperand() << ","
                 << right.getASMOperand() << ","
                 << to.getASMOperand()
                 << endl;
}

void CodeGenerator::generateOrStatement(Symbol left, Symbol right, Symbol to)
{
    this->output << "\tor.i " << left.getASMOperand() << ","
                 << right.getASMOperand() << ","
                 << to.getASMOperand()
                 << endl;
}

void CodeGenerator::generateJumpGreaterStatement(Symbol left, Symbol right, Symbol label)
{
    this->output << "\tjg.i " << left.getASMOperand() << ","
                 << right.getASMOperand() << ",#" << label.getSymbolName()
                 << endl;
}

CodeGenerator *codeGenerator = new CodeGenerator();