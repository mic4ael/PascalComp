#include "symboltable.hpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;


SymbolTable::SymbolTable()
{
    this->address = 0;
    this->temporaryVariableCount = 0;

    Symbol writeProc("write");
    writeProc.setSymbolType(PROCEDURE_SYMBOL);
    this->symbols.push_back(writeProc);

    Symbol readProc("read");
    readProc.setSymbolType(PROCEDURE_SYMBOL);
    this->symbols.push_back(readProc);

    Symbol exitProc("exit");
    exitProc.setSymbolType(PROCEDURE_SYMBOL);
    this->symbols.push_back(exitProc);
}

Symbol& SymbolTable::getSymbolByIndex(int tokenIndex)
{
    return this->symbols[tokenIndex];
}

int SymbolTable::lookupSymbol(const char *symbol)
{
    if (this->symbols.size() == 0)
    {
        return -1;
    }

    for (int i = 0; i < this->symbols.size(); ++i)
    {
        if (this->symbols[i].getSymbolName().compare(symbol) == 0)
        {
            return i;
        }
    }

    return -1;
}

int SymbolTable::lookupSymbol(int intValue)
{
    if (this->symbols.size() == 0)
    {
        return -1;
    }

    for (int i = 0; i < this->symbols.size(); ++i)
    {
        if (this->symbols[i].getSymbolValue().intValue == intValue)
        {
            return i;
        }
    }

    return -1;
}

int SymbolTable::lookupSymbol(double doubleValue)
{
    if (this->symbols.size() == 0)
    {
        return -1;
    }

    for (int i = 0; i < this->symbols.size(); ++i)
    {
        if (this->symbols[i].getSymbolValue().doubleValue == doubleValue)
        {
            return i;
        }
    }

    return -1;
}

int SymbolTable::createTemporaryVariable(VarType varType)
{
    string tmp = "$t";
    tmp += std::to_string(this->temporaryVariableCount);
    Symbol s(tmp);
    s.setVarType(varType);
    s.setSymbolType(VAR_SYMBOL);
    s.setAddress(this->address);
    this->address += varType == INT_TYPE ? 4 : 8;
    this->temporaryVariableCount += 1;
    this->symbols.push_back(s);
    return this->symbols.size() - 1;
}

int SymbolTable::insertSymbol(const char *symbol)
{
    Symbol s(symbol);
    this->symbols.push_back(s);
    return this->symbols.size() - 1;
}

int SymbolTable::insertSymbol(const char *symbol, VarType varType)
{
    Symbol s(symbol, varType);
    s.setAddress(this->address);
    this->symbols.push_back(s);
    this->address += varType == INT_TYPE ? 4 : 8;
    return this->symbols.size() - 1;
}

int SymbolTable::insertConstant(int intValue)
{
    Symbol s(intValue);
    s.setAddress(this->address);
    this->symbols.push_back(s);
    this->address += 4;
    return this->symbols.size() - 1;
}

int SymbolTable::insertConstant(double doubleValue)
{
    Symbol s(doubleValue);
    s.setAddress(this->address);
    this->symbols.push_back(s);
    this->address += 8;
    return this->symbols.size() - 1;
}

string SymbolTable::tableStr() {
    ostringstream out;
    out << "\nSymbol Table Dump" << endl;

    for (int i = 0; i < this->symbols.size(); ++i)
    {
        Symbol symbol = this->symbols[i];
        out << "; " << i << " Global ";

        switch (symbol.getSymbolType()) {
            case PROCEDURE_SYMBOL:
                out << "procedure " << symbol.getSymbolName() << endl;
                break;
            case FUNCTION_SYMBOL:
                out << "function " << symbol.getSymbolName() << endl;
                break;
            case LABEL_SYMBOL:
                out << "label " << symbol.getSymbolName() << endl;
                break;
            case VAR_SYMBOL:
                out << "variable " << symbol.getSymbolName();
                switch (symbol.getVarType()) {
                    case INT_TYPE:
                        out << " integer offset=" << symbol.getAddress() << endl;
                        address += 4;
                        break;
                    case REAL_TYPE:
                        out << " real offset=" << symbol.getAddress() << endl;
                        address += 8;
                        break;
                    case NONE_TYPE:
                        out << endl;
                        break;
                    }
                    break;
            case CONSTANT_SYMBOL:
                out << "constant " << symbol.getSymbolName() << endl;
                break;
            default:
                out << "NONE " << symbol.getSymbolName() << endl;
                break;
        }
    }

    return out.str();
}

void SymbolTable::increaseAddress(int increaseBy)
{
    this->address += increaseBy;
}

int SymbolTable::getAddress()
{
    return this->address;
}

SymbolTable *symbolTable = new SymbolTable();