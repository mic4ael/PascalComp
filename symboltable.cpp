#include "symboltable.hpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;


SymbolTable::SymbolTable()
{
    this->address = 0;
    this->temporaryVariableCount = 0;

    Symbol readProc("read");
    readProc.setSymbolType(PROCEDURE_SYMBOL);
    this->symbols.push_back(readProc);

    Symbol writeProc("write");
    writeProc.setSymbolType(PROCEDURE_SYMBOL);
    this->symbols.push_back(writeProc);

    // Symbol exitProc("exit");
    // exitProc.setSymbolType(PROCEDURE_SYMBOL);
    // this->symbols.push_back(exitProc);
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

    for (int j = 0; j < this->children.size(); ++j)
    {
        out << this->printTable(this->children[j]);
    }

    out << this->printTable(this);
    return out.str();
}

string SymbolTable::printTable(SymbolTable *table)
{
    ostringstream out;
    vector<Symbol> symbols = table->symbols;
    out << "\nSymbol Table Dump" << endl;
    int index = 0;
    for (int i = 0; i < symbols.size(); ++i)
    {
        Symbol symbol = symbols[i];

        switch (symbol.getSymbolType())
        {
        case PROCEDURE_SYMBOL:
            out << "; " << index++ << " Global procedure " << symbol.getSymbolName() << endl;
            break;
        case FUNCTION_SYMBOL:
            out << "; " << index++ << " Global function " << symbol.getSymbolName() << endl;
            break;
        case LABEL_SYMBOL:
            out << "; " << index++ << " Global label " << symbol.getSymbolName() << endl;
            break;
        case VAR_SYMBOL:
            out << "; " << index++ << " Global variable " << symbol.getSymbolName();
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
            out << "; " << index++ << " Local number ";
            if (symbol.getVarType() == INT_TYPE)
            {
                out << symbol.getSymbolValue().intValue
                    << " integer" << endl;
            } else {
                out << symbol.getSymbolValue().doubleValue
                    << " real" << endl;
            }

            break;
        default:
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

SymbolTable *SymbolTable::addNewSymbolTable(string name)
{
    SymbolTable *newTable = new SymbolTable();
    newTable->symbols = vector<Symbol>(this->symbols);
    newTable->parent = this;
    newTable->name = name;
    this->children.push_back(newTable);
    return newTable;
}

SymbolTable *symbolTable = new SymbolTable();