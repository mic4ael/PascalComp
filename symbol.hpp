#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <iostream>
#include <vector>

union SymbolValue
{
    int intValue;
    double doubleValue;
};

enum VarType
{
    INT_TYPE,
    REAL_TYPE,
    NONE_TYPE
};

enum SymbolType
{
    FUNCTION_SYMBOL,
    PROCEDURE_SYMBOL,
    LABEL_SYMBOL,
    VAR_SYMBOL,
    CONSTANT_SYMBOL,
    NONE_SYMBOL
};

class Symbol
{
public:
    Symbol();
    Symbol(int value);
    Symbol(double value);
    Symbol(std::string symbolName) : symbolName(symbolName)
    {
        this->references = -1;
        this->isReference = false;
        this->address = 0;
        this->type = NONE_TYPE;
        this->symbolType = NONE_SYMBOL;
    };
    Symbol(std::string symbolName, VarType varType) :symbolName(symbolName), type(varType)
    {
        this->references = -1;
        this->isReference = false;
        this->address = 0;
        this->type = NONE_TYPE;
        this->symbolType = NONE_SYMBOL;
    };

    ~Symbol();
    void setSymbolName(std::string name)
    {
        this->symbolName = name;
    }
    std::string getSymbolName();
    VarType getVarType();
    void setVarType(VarType varType)
    {
        this->type = varType;
    }
    SymbolValue getSymbolValue()
    {
        return this->value;
    }
    SymbolType getSymbolType()
    {
        return this->symbolType;
    }
    void setSymbolType(SymbolType symbolType);
    void setAddress(int address)
    {
        this->address = address;
    }

    int getAddress()
    {
        return this->address;
    }

    bool isSymbolReference()
    {
        return this->isReference;
    }

    void setIsReference(bool isReference)
    {
        this->isReference = isReference;
    }

    VarType getReturnType()
    {
        return this->returnType;
    }

    void setReturnType(VarType varType)
    {
        this->returnType = varType;
    }

    void setReferences(int references)
    {
        this->references = references;
    }

    int getReferences()
    {
        return this->references;
    }

private:
    std::string symbolName;
    SymbolValue value;
    VarType type;
    VarType returnType;
    SymbolType symbolType;
    bool isReference;
    int address;
    int references;
};

#endif