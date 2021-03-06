#include "symboltable.hpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;


SymbolTable::SymbolTable()
{
    this->nextLabelId = 0;
    this->children = new vector<SymbolTable *>();
    this->symbols = new vector<Symbol*>();
    this->address = 0;
    this->name = "global";
    this->localSpaceAddress = 0;
    this->lastLocalSpaceAddress = 0;
    this->enterArg = 0;
    this->temporaryVariableCount = 0;

    Symbol *readProc = new Symbol("read");
    readProc->setSymbolType(PROCEDURE_SYMBOL);
    this->symbols->push_back(readProc);

    Symbol *writeProc = new Symbol("write");
    writeProc->setSymbolType(PROCEDURE_SYMBOL);
    this->symbols->push_back(writeProc);

    // Symbol exitProc("exit");
    // exitProc.setSymbolType(PROCEDURE_SYMBOL);
    // this->symbols->push_back(exitProc);
}

SymbolTable::~SymbolTable()
{
    for (int i = 0; i < this->children->size(); ++i) {
        delete this->children->at(i);
    }
}

Symbol& SymbolTable::getSymbolByIndex(int tokenIndex)
{
    return *this->symbols->at(tokenIndex);
}

int SymbolTable::lookupSymbol(const char *symbol)
{
    if (this->symbols->size() == 0)
    {
        return -1;
    }

    for (int i = 0; i < this->symbols->size(); ++i)
    {
        Symbol *s = this->symbols->at(i);
        if (s->getSymbolName().compare(symbol) == 0)
        {
            if (this->name.compare("global") != 0 && !s->isLocalVar())
                continue;
            return i;
        }
    }

    return -1;
}

int SymbolTable::lookupSymbol(int intValue)
{
    if (this->symbols->size() == 0)
    {
        return -1;
    }

    for (int i = 0; i < this->symbols->size(); ++i)
    {
        Symbol *s = this->symbols->at(i);
        if (s->getSymbolType() != CONSTANT_SYMBOL)
            continue;
        if (s->getVarType() == INT_TYPE && s->getSymbolValue().intValue == intValue)
        {
            if (this->name.compare("global") != 0 && !s->isLocalVar())
                continue;
            return i;
        }
    }

    return -1;
}

int SymbolTable::lookupSymbol(double doubleValue)
{
    if (this->symbols->size() == 0)
    {
        return -1;
    }

    for (int i = 0; i < this->symbols->size(); ++i)
    {
        Symbol *s = this->symbols->at(i);
        if (s->getSymbolType() != CONSTANT_SYMBOL || s->isLocalVar())
            continue;
        if (s->getVarType() == REAL_TYPE && s->getSymbolValue().doubleValue == doubleValue)
        {
            if (this->name.compare("global") != 0 && !s->isLocalVar())
                continue;
            return i;
        }
    }

    return -1;
}

int SymbolTable::createTemporaryVariable(VarType varType)
{
    string tmp = "$t";
    if (this->getName().compare("global") == 0)
        tmp += std::to_string(this->temporaryVariableCount);
    else
        tmp += std::to_string(this->parent->temporaryVariableCount);
    
    Symbol *s = new Symbol(tmp);
    s->setVarType(varType);
    s->setSymbolType(VAR_SYMBOL);
    if (this->name.compare("global") != 0)
    {
        this->enterArg += (varType == INT_TYPE ? 4 : 8);
        s->setIsLocal(true);
        this->lastLocalSpaceAddress = this->localSpaceAddress;
        this->localSpaceAddress -= (varType == INT_TYPE ? 4 : 8);
        s->setAddress(this->enterArg * -1);
    }
    else
    {
        s->setAddress(this->address);
        s->setIsLocal(false);
        this->address += varType == INT_TYPE ? 4 : 8;
    }

    if (this->getName().compare("global") == 0)
        this->temporaryVariableCount += 1;
    else
        this->parent->temporaryVariableCount += 1;
    this->symbols->push_back(s);
    return this->symbols->size() - 1;
}

int SymbolTable::insertSymbol(const char *symbol)
{
    for (int i = 0; i < this->symbols->size(); ++i)
    {
        Symbol *s = this->symbols->at(i);
        if (s->getSymbolName().compare(symbol) == 0)
        {
            if (this->name.compare("global") != 0 && !s->isLocalVar())
                continue;
            return i;
        }
    }

    Symbol *s = new Symbol(symbol);
    if (this->name.compare("global") != 0)
    {
        s->setIsLocal(true);
    }
    this->symbols->push_back(s);
    return this->symbols->size() - 1;
}

int SymbolTable::insertArray(VarType arrayType)
{
    Symbol *s = new Symbol();
    if (arrayType == INT_TYPE)
    {
        s->setVarType(ARRAY_INT_TYPE);
    }
    else
    {
        s->setVarType(ARRAY_REAL_TYPE);
    }

    if (this->name.compare("global") != 0)
    {
        s->setIsLocal(true);
    }

    s->setAddress(this->address);
    this->symbols->push_back(s);
    return this->symbols->size() - 1;
}

int SymbolTable::insertSymbol(const char *symbol, VarType varType)
{
    for (int i = 0; i < this->symbols->size(); ++i)
    {
        Symbol *s = this->symbols->at(i);
        if (s->getSymbolName().compare(symbol) == 0)
        {
            if (this->name.compare("global") != 0 && !s->isLocalVar())
                continue;
            return i;
        }
    }

    Symbol *s = new Symbol(symbol, varType);
    s->setAddress(this->address);
    if (this->name.compare("global") != 0)
    {
        s->setIsLocal(true);
    }
    this->symbols->push_back(s);
    this->address += varType == INT_TYPE ? 4 : 8;
    return this->symbols->size() - 1;
}

int SymbolTable::insertConstant(int intValue)
{
    for (int i = 0; i < this->symbols->size(); ++i)
    {
        Symbol symbol = *this->symbols->at(i);
        if (symbol.getVarType() == INT_TYPE && symbol.getSymbolType() == CONSTANT_SYMBOL && symbol.getSymbolValue().intValue == intValue)
        {
            if (this->name.compare("global") != 0 && !symbol.isLocalVar())
                continue;
            return i;
        }
    }

    Symbol *s = new Symbol(intValue);
    s->setAddress(this->address);
    if (this->name.compare("global") != 0)
    {
        s->setIsLocal(true);
    }
    this->symbols->push_back(s);
    return this->symbols->size() - 1;
}

int SymbolTable::insertDoubleConstant(double doubleValue)
{
    for (int i = 0; i < this->symbols->size(); ++i)
    {
        Symbol symbol = *this->symbols->at(i);
        if (symbol.getVarType() == REAL_TYPE && symbol.getSymbolType() == CONSTANT_SYMBOL && symbol.getSymbolValue().doubleValue == doubleValue)
        {
            return i;
        }
    }

    Symbol *s = new Symbol(doubleValue);
    s->setAddress(this->address);
    if (this->name.compare("global") != 0)
    {
        s->setIsLocal(true);
    }
    this->symbols->push_back(s);
    return this->symbols->size() - 1;
}

string SymbolTable::tableStr() {
    ostringstream out;

    for (int j = 0; j < this->children->size(); ++j)
    {
        out << this->printTable(this->children->at(j));
    }

    out << this->printTable(this);
    return out.str();
}

string SymbolTable::printTable(SymbolTable *table)
{
    ostringstream out;
    vector<Symbol*> *symbols = table->symbols;
    out << "Symbol Table Dump " << table->getName() << endl;
    int index = 0;
    for (int i = 0; i < symbols->size(); ++i)
    {
        Symbol *symbol = symbols->at(i);
        switch (symbol->getSymbolType())
        {
        case PROCEDURE_SYMBOL:
            out << "; " << index++ << " Global procedure " << symbol->getSymbolName() << endl;
            break;
        case FUNCTION_SYMBOL:
            out << "; " << index++ << " Global function " << symbol->getSymbolName() 
                << (symbol->getReturnType() == REAL_TYPE ? " real" : " integer")
                << endl;
            break;
        case LABEL_SYMBOL:
            out << "; " << index++ << (symbol->isLocalVar() ? " Local " : " Global ")
                << "label " << symbol->getSymbolName() << endl;
            break;
        case VAR_SYMBOL:
        case ARGUMENT_SYMBOL:
            out << "; " << index++;

            if (symbol->isSymbolReference())
            {
                if (table->getName().compare("global") != 0)
                    out << " Local reference variable ";
                else
                    out << " Global reference variable ";
                out << symbol->getSymbolName();
            }
            else
            {
                if (symbol->isLocalVar())
                {
                    out << " Local variable " << symbol->getSymbolName();
                }
                else
                {
                    out << " Global variable " << symbol->getSymbolName();
                }
            }
            switch (symbol->getVarType()) {
                case INT_TYPE:
                    out << " integer offset=" << symbol->getAddress() << endl;
                    address += 4;
                    break;
                case REAL_TYPE:
                    out << " real offset=" << symbol->getAddress() << endl;
                    address += 8;
                    break;
                case ARRAY_INT_TYPE:
                    out << " array [" << symbol->getLowerIndex() << ".." << symbol->getUpperIndex() << "]"
                        << " of integer" << " offset="
                        << symbol->getAddress() << endl;
                    break;
                case ARRAY_REAL_TYPE:
                    out << " array [" << symbol->getLowerIndex() << ".." << symbol->getUpperIndex() << "]"
                        << " of real" << " offset="
                        << symbol->getAddress() << endl;
                    break;
                case NONE_TYPE:
                    out << endl;
                    break;
                }
                break;
        case CONSTANT_SYMBOL:
            out << "; " << index++;
            if (!symbol->isLocalVar())
            {
                out << " Global number ";
            }
            else
            {
                out << " Local number ";
            }
            if (symbol->getVarType() == INT_TYPE)
            {
                out << symbol->getSymbolName()
                    << " integer" << endl;
            } else {
                out << symbol->getSymbolName()
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
    SymbolTable *newTable = new SymbolTable;
    newTable->address = 8;
    newTable->localSpaceAddress = -4;
    newTable->symbols = new vector<Symbol *>;
    newTable->parent = this;
    newTable->name = name;

    for (int i = 0; i < this->symbols->size(); ++i)
    {
        Symbol *s = this->symbols->at(i);
        if (s->getSymbolType() == ARGUMENT_SYMBOL)
            continue;
        if (s->getSymbolType() == VAR_SYMBOL && s->isLocalVar())
            continue;
        newTable->symbols->push_back(this->symbols->at(i));
    }

    this->children->push_back(newTable);
    return newTable;
}

Symbol* SymbolTable::lookupFuncReturnReference(string funcName)
{
    for (int i = 0; i < this->symbols->size(); ++i) {
        Symbol *it = this->symbols->at(i);
        if (it->getSymbolName().compare(funcName) == 0 && it->isSymbolReference()) {
            return it;
        }
    }

    return NULL;
}

int SymbolTable::lookupReturnVariable(Symbol funcSymbol)
{
    return this->createTemporaryVariable(funcSymbol.getReturnType());
}

int SymbolTable::createReference(string name, VarType type)
{
    Symbol *s = new Symbol(name);
    if (this->name.compare("global") != 0)
    {
        s->setIsLocal(true);
    }
    s->setVarType(type);
    s->setSymbolType(VAR_SYMBOL);
    s->setIsReference(true);
    s->setAddress(this->address);
    this->address += 4;
    this->symbols->push_back(s);
    return this->symbols->size() - 1;
}

int SymbolTable::createLabel(bool pending)
{
    string labelName;
    if (this->name.compare("global") == 0)
        labelName = "lab" + std::to_string(this->nextLabelId++);
    else
        labelName = "lab" + std::to_string(this->parent->nextLabelId++);
    Symbol *s = new Symbol(labelName);
    if (this->name.compare("global") == 0)
        s->setIsLocal(false);
    else
        s->setIsLocal(true);
    s->setSymbolType(LABEL_SYMBOL);
    if (pending)
    {
        this->pendingLabels.push_back(labelName);
    }
    this->symbols->push_back(s);
    return this->symbols->size() - 1;
}

string SymbolTable::getNextLabel(bool remove)
{
    string ret = this->pendingLabels[0];
    if (this->pendingLabels.size() == 0)
        return "";
    if (remove)
        this->pendingLabels.erase(this->pendingLabels.begin());
    return ret;
}

SymbolTable *symbolTable = new SymbolTable();